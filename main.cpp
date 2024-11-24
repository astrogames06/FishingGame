#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "load_imgs.h"

enum GAME_STATE
{
	MENU,
	GAME,
	LOSE
};
GAME_STATE game_state = GAME;

const int WIDTH = 850;
const int HEIGHT = 450;

Font font;

struct Fish
{
	int x;
	int y;
	Texture2D tex;
	bool direction = false;
	bool caught = false;
};
std::vector<Fish> fishes;
bool fish_caught = false;

int score = 0;

void UpdateDrawFrame();

int main(void)
{
	InitWindow(WIDTH, HEIGHT, "Fishing Game");
	LoadImgs();

	font = LoadFontFromImage(font_img, MAGENTA, 10);

	for (int i = 0; i < 20; i++)
	{
		Texture2D fish_tex = LoadTextureFromImage(fish_imgs[GetRandomValue(0, fish_imgs.size()-1)]);
		fishes.push_back(Fish{GetRandomValue(fish_tex.width, WIDTH-fish_tex.width), GetRandomValue(HEIGHT-128, HEIGHT-water_tex.height-64), fish_tex});
	}

	#if defined(PLATFORM_WEB)
    	emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
	#else
		//SetTargetFPS(60);   // Set our game to run at 60 frames-per-second
		//--------------------------------------------------------------------------------------

		// Main game loop
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			UpdateDrawFrame();
		}
	#endif

	CloseWindow();

	return 0;
}

void UpdateDrawFrame()
{
	BeginDrawing();
	
	
	// std::cout << "Font base size: " << font.baseSize << std::endl;
	// std::cout << "Glyph count: " << font.glyphCount << std::endl;

	if (game_state == GAME)
	{
		ClearBackground(WHITE);

		DrawFPS(20, HEIGHT-20);

		DrawTexture(boat_tex, WIDTH/2-boat_tex.width/2, 50, WHITE);
		DrawTexture(water_tex, 0, HEIGHT-water_tex.height-64, WHITE);
		DrawTexture(floor_tex, 0, HEIGHT-floor_tex.height, WHITE);

		DrawLine(GetMouseX(), 0, GetMouseX(), GetMouseY(), BLACK);

		for (int i = 0; i < fishes.size(); i++)
		{
			Fish& fish = fishes[i];

			if (!fish.caught)
			{
				if (!fish.direction)
				{
					fish.x += 5;
				}
				else
				{
					fish.x -= 5;
				}

				if (fish.x > WIDTH-fish.tex.width || fish.x < 0)
				{
					Image flipped = LoadImageFromTexture(fish.tex);
					ImageFlipHorizontal(&flipped);

					fish.tex = LoadTextureFromImage(flipped);
					UnloadImage(flipped);

					fish.direction = !fish.direction;
				}
				if (fish.x > WIDTH-fish.tex.width) fish.x = WIDTH-fish.tex.width;
				if (fish.x < 0) fish.x = 0;
			}
			
			if (fish.caught)
			{
				fish.x = GetMouseX() - fish.tex.width/2;
				fish.y = GetMouseY() - fish.tex.height/2;

				if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
				{
					if (GetMouseY() <= 130)
					{
						fish.caught = false;
						fishes.erase(fishes.begin() + i);
						fish_caught = false;

						score++;
						continue;
					}
					else if (GetMouseY() > 130)
					{
						fish.caught = false;
						fish_caught = false;
						// fish.x = GetRandomValue(fish.tex.width, WIDTH-fish.tex.width);
						// fish.y = GetRandomValue(HEIGHT-128, HEIGHT-water_tex.height-64);
					}
				}
			}

			if (CheckCollisionPointRec(
				GetMousePosition(), 
				{(float)fish.x, (float)fish.y, (float)fish.tex.width, (float)fish.tex.height
			}) && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !fish_caught)
			{
				fish.caught = true;
				fish_caught = true;
				std::cout << fish.caught << '\n';
			}

			DrawTexture(fish.tex, fish.x, fish.y, WHITE);
			DrawTextureRec(fish.tex, (Rectangle){ 0, 0, (float)fish.tex.width, (float)fish.tex.height }, (Vector2){ (float)fish.x, (float)fish.y }, WHITE);
		}

		if (fishes.size() <= 0)
		{
			game_state = LOSE;
		}
	}
	else if (game_state == MENU)
	{
		ClearBackground(WHITE);
	}
	else if (game_state == LOSE)
	{
		ClearBackground(BLACK);
		DrawText("NO FISH!", WIDTH/2, 200, 40, WHITE);
	}
	
	std::string score_text = "Score: " + std::to_string(score);
	DrawText(score_text.c_str(), 20, 20, 20, BLACK);

	EndDrawing();
}