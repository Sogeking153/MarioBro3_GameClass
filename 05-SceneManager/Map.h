#pragma once
#include "Textures.h"
#include "Sprites.h"

class Map
{
	int width_tileset = 16 * 3;
	int height_tileset = 16 * 3;

	int width_map = 176;
	int height_map = 41;


	LPCWSTR mapFilePath = L"textures\\map_world1-1.txt";
	int map[200][200];
public:
	Map();
	~Map();
	void LoadTileSet();
	void Draw();
};

