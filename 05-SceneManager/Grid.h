#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Mario.h"


//173 186.25
#define CELL_HEIGHT (692/4.0f)
#define CELL_WIDTH (745/4.0f)

// 12 48
//#define MAX_ROW (int)(SCENE_HEIGHT/CELL_HEIGHT) + 1
//#define MAX_COLUMN (int)(SCENE_WIDTH/CELL_WIDTH) + 1
#define MAX_ROW 20
#define MAX_COLUMN 47

class CGrid
{
public:
	CMario* player = NULL;

	vector<LPGAMEOBJECT> total_obj;
	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> items;
	vector<LPGAMEOBJECT> bricks_blink;

	vector<LPGAMEOBJECT> cells[MAX_ROW][MAX_COLUMN];

	LPCWSTR objFilePath;
	LPCWSTR gridFilePath;

	void Classify(LPGAMEOBJECT obj);

	// take obj in filter cam and put in playscene
	void GetListObjInGrid(float cam_x, float cam_y);
	
	//update obj from cell to cell
	void UpdatePositionInGrid(float cam_x, float cam_y);

	LPGAMEOBJECT CreateNewObj(int id_grid, int obj_type, float x, float y, float w, float h, int extra0, int extra1);

	void ReadFileObj();
	void ReadFileGrid();

	CGrid(LPCWSTR objFilePath, LPCWSTR gridFilePath, CMario* mario);
	~CGrid() {};
};
