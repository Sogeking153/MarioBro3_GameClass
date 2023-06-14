#include "Grid.h"
#include "Goomba.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <fstream>
#include "debug.h"
#include "PlayScene.h"
#include "BrickCoin.h"
#include "Koopa.h"
#include "VenusFireTrap.h"
#include "PiranaPlant.h"
#include "Coin.h"
#include "BrickBlink.h"
#include "RandomBonus.h"

#include "Utils.h"
#include "AssetIDs.h"

void CGrid::Classify(LPGAMEOBJECT obj)
{
	//type is use to create different type of same object also for sorting in grid
	if (obj->type == OBJECT_TYPE_COIN || obj->type == OBJECT_TYPE_BRICK_COIN || obj->type == OBJECT_TYPE_RANDOM_BONUS)
		items.push_back(obj);
	/*else if (obj->type == OBJECT_TYPE_BRICK_BLINK)
		bricks_blink.push_back(obj);*/
	else
		enemies.push_back(obj);
}

void CGrid::GetListObjInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();

	enemies.clear();
	items.clear();
	//bricks_blink.clear();

	int top = (int)((cam_y) / CELL_HEIGHT);
	int bottom = (int)((cam_y + SCREEN_HEIGHT) / CELL_HEIGHT);

	int left = (int)((cam_x) / CELL_WIDTH);
	int right = (int)((cam_x + SCREEN_WIDTH) / CELL_WIDTH);

	for (int i = top - BORDER_COLUMN_GRID_GET_OBJ; i <= bottom + BORDER_COLUMN_GRID_GET_OBJ; i++)
		for (int j = left - BORDER_ROW_GRID_GET_OBJ ; j <= right; j++)
		{	//can -2 for testing

			if (j < 0) j = 0;
			if (i < 0) i = 0;
			/*DebugOut(L"i %d\n", i);
			DebugOut(L"j %d\n", j);
			DebugOut(L"size %d\n", cells[i][j].size());*/

			for (int k = 0; k < cells[i][j].size(); k++) {
				//DebugOut(L"id %d\n", cells[i][j].at(k)->id);
				//if (cells[i][j].at(k)->GetHealth()) {
				if (cells[i][j].at(k)->is_appeared == false && cells[i][j].at(k)->isDeleted == false) // if hasnt appear nor die
					//{//  && // is_appeared: ex appear in 4 take 1 cell
					//if (j >= left && j <= right)

					//&& cells[i][j].at(k)->used == false
				{
					Classify(cells[i][j].at(k));
					cells[i][j].at(k)->is_appeared = true; // ?? why recover has to be in playscene
				}
				//}
					//if (!cells[i][j].at(k)->is_in_grid && cells[i][j].at(k)->is_appeared) {

					//	cells[i][j].at(k)->is_in_grid = true;
				//	}

				//}
			}
		}


	//keep
	//game->GetCurrentScene()->SetEnemiesInScene(enemies);

	//game->GetCurrentScene()->SetItemsInScene(items);
	//game->GetCurrentScene()->SetBrickInScene(bricks);

	//dynamic_cast<ParaGoompa*>(e->obj);
	//dynamic_cast<PlayScene*>(game->GetCurrentScene());

	//if (dynamic_cast<CPlayScene*>(game->GetCurrentScene()))
	//{
	dynamic_cast<CPlayScene*>(game->GetCurrentScene())->SetEnemiesInScene(enemies);
	dynamic_cast<CPlayScene*>(game->GetCurrentScene())->SetItems(items);
	//dynamic_cast<CPlayScene*>(game->GetCurrentScene())->SetBrickBlink(bricks_blink);
	//}
}

void CGrid::UpdatePositionInGrid(float cam_x, float cam_y)
{
	CGame* game = CGame::GetInstance();
	int top_cell = (int)((cam_y) / CELL_HEIGHT);
	int bottom_cell = (int)((cam_y + SCREEN_HEIGHT) / CELL_HEIGHT) - 1;

	int left_cell = (int)((cam_x) / CELL_WIDTH);
	int right_cell = (int)((cam_x + SCREEN_WIDTH) / CELL_WIDTH);


	if (dynamic_cast<CPlayScene*>(game->GetCurrentScene()))
	{
		enemies.clear();
		items.clear();
		//bricks_blink.clear();

		CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
		enemies = scene->enemies;
		for (int m = 0; m < enemies.size(); m++) {
			LPGAMEOBJECT enemy = enemies[m];

			for (int i = top_cell - BORDER_COLUMN_GRID; i <= bottom_cell + BORDER_COLUMN_GRID; i++)
				for (int j = left_cell - BORDER_ROW_GRID; j <= right_cell + BORDER_ROW_GRID; j++) {
					if (j < 0) j = 0;
					if (i < 0) i = 0;
					for (int k = 0; k < cells[i][j].size(); k++) {
						if (cells[i][j].at(k)->id_grid == enemy->id_grid) {
							cells[i][j].erase(cells[i][j].begin() + k);
						}
					}
				}

			int top = (int)(enemy->GetY() / CELL_HEIGHT);
			int bottom = (int)((enemy->GetY() + enemy->h) / CELL_HEIGHT);
			int left = (int)(enemy->GetX() / CELL_WIDTH);
			int right = (int)((enemy->GetX() + enemy->w) / CELL_WIDTH);

			for (int i = top; i <= bottom; i++)
				for (int j = left; j <= right; j++) {
					cells[i][j].push_back(enemy);
				}
		}

		items = scene->items;
		for (int m = 0; m < items.size(); m++) {
			LPGAMEOBJECT item = items[m];

			for (int i = top_cell - BORDER_COLUMN_GRID; i <= bottom_cell + BORDER_COLUMN_GRID; i++)
				for (int j = left_cell - BORDER_ROW_GRID; j <= right_cell + BORDER_ROW_GRID; j++) {
					if (j < 0) j = 0;
					if (i < 0) i = 0;
					for (int k = 0; k < cells[i][j].size(); k++) {
						if (cells[i][j].at(k)->id_grid == item->id_grid) {
							cells[i][j].erase(cells[i][j].begin() + k);
						}
					}
				}

			int top = (int)(item->GetY() / CELL_HEIGHT);
			int bottom = (int)((item->GetY() + item->h) / CELL_HEIGHT);
			int left = (int)(item->GetX() / CELL_WIDTH);
			int right = (int)((item->GetX() + item->w) / CELL_WIDTH);

			for (int i = top; i <= bottom; i++)
				for (int j = left; j <= right; j++) {
					cells[i][j].push_back(item);
				}
		}

		/*bricks_blink = scene->list_bricklink;
		for (int m = 0; m < bricks_blink.size(); m++) {
			LPGAMEOBJECT blink = bricks_blink[m];

			for (int i = top_cell - BORDER_COLUMN_GRID; i <= bottom_cell + BORDER_COLUMN_GRID; i++)
				for (int j = left_cell - BORDER_ROW_GRID; j <= right_cell + BORDER_ROW_GRID; j++) {
					if (j < 0) j = 0;
					if (i < 0) i = 0;
					for (int k = 0; k < cells[i][j].size(); k++) {
						if (cells[i][j].at(k)->id_grid == blink->id_grid) {
							cells[i][j].erase(cells[i][j].begin() + k);
						}
					}
				}

			int top = (int)(blink->GetY() / CELL_HEIGHT);
			int bottom = (int)((blink->GetY() + blink->h) / CELL_HEIGHT);
			int left = (int)(blink->GetX() / CELL_WIDTH);
			int right = (int)((blink->GetX() + blink->w) / CELL_WIDTH);

			for (int i = top; i <= bottom; i++)
				for (int j = left; j <= right; j++) {
					cells[i][j].push_back(blink);
				}
		}*/
	}
}

LPGAMEOBJECT CGrid::CreateNewObj(int id_grid, int obj_type, float x, float y, float w, float h, int extra0, int extra1)
{
	///CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	//CGameObject* obj = NULL;
	CGameObject* obj=NULL;

	switch (obj_type)
	{

	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y, player); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_PARA_GOOMBA: obj = new ParaGoomba(x, y, player); break;

	case OBJECT_TYPE_BRICK_COIN:
	{
		int has_item = extra0;
		obj = new BrickCoin(x, y, has_item, player); break;
	}
	case OBJECT_TYPE_KOOPA:
	{
		int type = extra0;
		int state = extra1;

		obj = new Koopa(x, y, player, type, state); break;
	}

	case OBJECT_TYPE_VENUS_FIRE_TRAP:
	{
		int type = extra0;
		obj = new VenusFireTrap(x, y, player, type); break;
	}
	case OBJECT_TYPE_PIRANA_PLANT:
	{
		obj = new PiranaPlant(x, y, player); break;
	}
	case OBJECT_TYPE_BRICK_BLINK:
	{

		obj = new BrickBlink(x, y, player); break;
	}

	case OBJECT_TYPE_RANDOM_BONUS:
	{
		CMario* mario = dynamic_cast<CMario*>(player);
		obj = new RandomBonus(x, y, mario); break;
	}
		/*case 7:
		{
			int lv = type;
			obj = new VenusFireTrap(player, lv);
			//obj->SetState(VENUS_STATE_GOING_UP);
			break;
		}
		case 8:
		{
			//int lv = atof(tokens[4].c_str());
			obj = new PiranaPlant(player);
			//obj->SetState(PIRANA_PLANT_STATE_GOING_UP);
			break;
		}
		case 4:
		{
			obj = new CConCo(player, y);
			dynamic_cast<CConCo*>(obj)->type = type;
			break;
		}
		case 5:
		{
			obj = new ParaGoomba(player);
			//obj->SetState(PARA_GROOMBA_STATE_JUMP_BIG);
			break;
		}
		case 15:
		{
			//int state = atof(tokens[4].c_str());
			obj = new MovingFlatform(player);
			break;
		}
		case 11:
		{
			//int lv = atof(tokens[4].c_str());
			obj = new BrickBlink(player);
			//obj->SetState(BRICK_COIN_STATE_NOT_HIT);
			break;
		}*/

	}


	obj->SetPosition(x, y);
	obj->SetType(obj_type);
	obj->SetWidth((int)w);
	obj->SetHeight((int)h);
	obj->SetIdGrid(id_grid);

	//LPANIMATION_SET ani_set = animation_sets->Get(ani_id);

	//obj->SetAnimationSet(ani_set);

	return obj;
	//return NULL;
}

void CGrid::ReadFileObj()
{
	ifstream f;
	f.open(objFilePath);
	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		if (line[0] == '#') {
			continue;
		}
		if (tokens.size() < 6) continue;
		int id_grid = atoi(tokens[0].c_str());
		int obj_type = atoi(tokens[1].c_str());
		float x = atof(tokens[2].c_str());
		float y = atof(tokens[3].c_str());

		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int extra0 = atoi(tokens[6].c_str());
		int extra1 = atoi(tokens[7].c_str());
		//int extra2 = atoi(tokens[8].c_str());


		//AddObjectIntoGrid(object_type, x, y, w, h, ani_id, type, extra);
		LPGAMEOBJECT obj = CreateNewObj(id_grid, obj_type, x, y, w, h, extra0, extra1);
		total_obj.push_back(obj);
	}

	DebugOut(L"total obj la---------------] DINPUT::GetDeviceData failed. Error: %d\n", total_obj.size());
	f.close();

	//LPGAMEOBJECT obj = CreateNewObj(2, 672,1152, 48, 48, 0, 0, 0, 1, 1, 9);
	//total_obj.push_back(obj);
	//9	2	672	1152	48	48	5	2	100
}

void CGrid::ReadFileGrid()
{
	//objs.clear();
	ifstream f;
	f.open(gridFilePath);
	char str[MAX_SCENE_LINE];

	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		vector<string> tokens = split(line);
		if (line[0] == '#') {
			continue;
		}
		if (tokens.size() < 3) continue;
		int i = atoi(tokens[0].c_str());
		int j = atoi(tokens[1].c_str());

		//take id then find in object
		for (int k = 2; k < tokens.size(); k++) {
			int id = atoi(tokens[k].c_str());
			for (LPGAMEOBJECT obj : total_obj) // run in object list to find match id
				if (id == obj->id_grid) {
					cells[i][j].push_back(obj);
				}

		}
	}

	f.close();

	//DebugOut(L"[EEEEEEEEEEEEEEE] DINPUT::GetDeviceData failed. Error: %d\n", cells[6][14].size());
}

CGrid::CGrid(LPCWSTR objFilePath, LPCWSTR gridFilePath, CMario* mario)
{
	//DebugOut(L"new\n");
	this->objFilePath = objFilePath;
	this->gridFilePath = gridFilePath;

	player = mario;
}