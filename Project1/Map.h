#pragma once
#include "Textures.h"
#include "Sprites.h"

class Map
{
	int width_tileset = 16 * 3;
	int height_tileset = 16 * 3;

	//int width_map = 20;
	//int height_map = 20;
	//LPCWSTR mapFilePath = L"textures\\map20x20.txt";

	int width_map = 176;
	int height_map = 41;


	LPCWSTR mapFilePath = L"textures\\map_thanh.txt";
	int map[200][200];
public:
	Map();
	~Map();
	void LoadTileSet();
	void Draw();
};

