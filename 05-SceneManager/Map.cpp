#include "Map.h"
#include <iostream>
#include <fstream>
#include "debug.h"
#include "Textures.h"
#include "Game.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadTileSet()
{
	int a, b;
	ifstream f;
	f.open(mapFilePath);

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


	textures->Add(100, L"textures\\TileObject.png");

	int id = 0;
	CSprites* sprites = CSprites::GetInstance();


	LPTEXTURE titleset = textures->Get(100);



	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 29; j++)
		{
			sprites->Add(id++, j * width_tileset, i * height_tileset,
				j * width_tileset + width_tileset, i * height_tileset + height_tileset, titleset);
		}
	}
}

void Map::Draw()
{
	CSprites* sprites = CSprites::GetInstance();

	int w = 48;
	int h = 48;

	int  SCREEN_WIDTH = 760;
	int  SCREEN_HEIGHT = 730;

	float cam_x = 0, cam_y = 0;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);

	int begin_row = cam_y / w + 1;
	int end_row = (cam_y + SCREEN_HEIGHT) / w - 1;

	if (begin_row < 0)
		begin_row = 0;


	int begin_column = cam_x / h; 
	int end_column = (cam_x + SCREEN_WIDTH) / h + 1;

	if (begin_column < 0)
		begin_column = 0;

	//DebugOut(L"end row %d \n", end_row);
	//DebugOut(L"end column %d \n", end_column);


	//CSprites* sprites = CSprites::GetInstance();

	for (int i = begin_row; i < end_row; i++)
	{
		for (int j = begin_column; j < end_column; j++)
		{
			if (map[i][j] <= 0)
				continue;

			sprites->Get(map[i][j] - 1)->Draw(j * width_tileset, (i)*height_tileset);
		}

	}

}