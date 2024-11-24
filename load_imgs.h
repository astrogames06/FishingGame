#ifndef LOAD_IMGS_H
#define LOAD_IMGS_H

#include <raylib.h>

#include "assets/font.h"

#include "assets/floor_img.h"
#include "assets/water_img.h"
#include "assets/boat_img.h"

#include "assets/blue_img.h"
#include "assets/green_img.h"
#include "assets/puff_img.h"
#include "assets/red_img.h"

Image font_img;

Image floor_img;
Texture2D floor_tex;

Image water_img;
Texture2D water_tex;

Image boat_img;
Texture2D boat_tex;

Image blue;
Texture2D blue_tex;
Image green;
Texture2D green_tex;
Image puff;
Texture2D puff_tex;
Image red;
Texture2D red_tex;

std::vector<Image> fish_imgs;

void LoadImgs()
{
    //ExportImageAsCode(LoadImage("assets/font.png"), "assets/font.h");

    font_img.data = FONT_DATA;
    font_img.width = FONT_WIDTH;
    font_img.height = FONT_HEIGHT;
    font_img.format = FONT_FORMAT;
    font_img.mipmaps = 1;

    floor_img.data = FLOOR_IMG_DATA;
	floor_img.width = FLOOR_IMG_WIDTH;
	floor_img.height = FLOOR_IMG_HEIGHT;
	floor_img.format = FLOOR_IMG_FORMAT;
	floor_img.mipmaps = 1;
	floor_tex = LoadTextureFromImage(floor_img);

	water_img.data = WATER_IMG_DATA;
	water_img.width = WATER_IMG_WIDTH;
	water_img.height = WATER_IMG_HEIGHT;
	water_img.format = WATER_IMG_FORMAT;
	water_img.mipmaps = 1;
	water_tex = LoadTextureFromImage(water_img);

    boat_img.data = BOAT_IMG_DATA;
	boat_img.width = BOAT_IMG_WIDTH;
	boat_img.height = BOAT_IMG_HEIGHT;
	boat_img.format = BOAT_IMG_FORMAT;
	boat_img.mipmaps = 1;
	boat_tex = LoadTextureFromImage(boat_img);

    // fishes
    blue.data = BLUE_IMG_DATA;
	blue.width = BLUE_IMG_WIDTH;
	blue.height = BLUE_IMG_HEIGHT;
	blue.format = BLUE_IMG_FORMAT;
	blue.mipmaps = 1;
	blue_tex = LoadTextureFromImage(blue);

    green.data = GREEN_IMG_DATA;
	green.width = GREEN_IMG_WIDTH;
	green.height = GREEN_IMG_HEIGHT;
	green.format = GREEN_IMG_FORMAT;
	green.mipmaps = 1;
	green_tex = LoadTextureFromImage(green);

    puff.data = PUFF_IMG_DATA;
	puff.width = PUFF_IMG_WIDTH;
	puff.height = PUFF_IMG_HEIGHT;
	puff.format = PUFF_IMG_FORMAT;
	puff.mipmaps = 1;
	puff_tex = LoadTextureFromImage(puff);

    red.data = RED_IMG_DATA;
	red.width = RED_IMG_WIDTH;
	red.height = RED_IMG_HEIGHT;
	red.format = RED_IMG_FORMAT;
	red.mipmaps = 1;
	red_tex = LoadTextureFromImage(red);

    fish_imgs = {blue, green, puff, red};
}


#endif