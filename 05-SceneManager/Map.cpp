#include "Map.h"
#include <iostream>
#include <fstream>
#include "debug.h"
#include "Textures.h"
#include "Game.h"

Map::Map(LPCWSTR maptext, LPCWSTR tileset, int width_map, int height_map,
	int number_tile_set_width, int number_tile_set_height)
{
	this->mapTextFilePath = maptext;
	this->tileSetFilePath = tileset;

	this->width_map = width_map;
	this->height_map = height_map;

	this->number_tile_set_width = number_tile_set_width;
	this->number_tile_set_height = number_tile_set_height;
}

void Map::LoadTileSet()
{
	//int a, b;
	ifstream f;
	f.open(mapTextFilePath);

	for (int i = 0; i < height_map; i++)
	{
		for (int j = 0; j < width_map; j++)
		{
			f >> map[i][j];

			//DebugOut(L"value: %d \n", map[i][j]);
		}
	}

	f.close();

	CTextures* textures = CTextures::GetInstance();


	textures->Add(ID_MAP_TILE_SET, tileSetFilePath);//"textures\\TileObject.png"

	int id = 0;
	CSprites* sprites = CSprites::GetInstance();


	LPTEXTURE titleset = textures->Get(ID_MAP_TILE_SET);



	for (int i = 0; i < number_tile_set_height; i++)
	{
		for (int j = 0; j < number_tile_set_width; j++)
		{
			sprites->Add(id++, j * width_tile, i * height_tile,
				j * width_tile + width_tile, i * height_tile + height_tile, titleset);
		}
	}
}

void Map::Draw()
{
	CSprites* sprites = CSprites::GetInstance();

	//int w = 48;
	//int h = 48;



	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	int begin_row = (int)cam_y / width_tile + 1;
	int end_row = (int)(cam_y + SCREEN_HEIGHT) / width_tile - 1;

	if (begin_row < MIN_ROW)
		begin_row = MIN_ROW;


	int begin_column = (int)cam_x / height_tile;
	int end_column = (int)	(cam_x + SCREEN_WIDTH) / height_tile + 1;

	if (begin_column < MIN_COLUMN)
		begin_column = MIN_COLUMN;

	//DebugOut(L"end row %d \n", end_row);
	//DebugOut(L"end column %d \n", end_column);


	//CSprites* sprites = CSprites::GetInstance();

	for (int i = begin_row; i < end_row; i++)
	{
		for (int j = begin_column; j < end_column; j++)
		{
			if (map[i][j] <= IS_NOT_COLOURED_TILE)
				continue;

			sprites->Get(map[i][j] - 1)->Draw((float)j * width_tile, (float)(i)*height_tile);
		}

	}

}