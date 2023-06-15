#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "FlatForm.h"
#include "BrickCoin.h"
#include "Mushroom.h"
#include "SuperLeaf.h"
#include "Koopa.h"
#include "Pipe.h"
#include "PlantBullet.h"
#include "VenusFireTrap.h"
#include "BrickBlink.h"
#include "BrickDebris.h"
#include "PButton.h"
#include "RandomBonus.h"
#include "UI.h"
#include "VirtualBox.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
	map = NULL;
	grid = NULL;
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAP	3
#define SCENE_SECTION_OBJECTS_GRID 4

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ASSETS_SECTION_SPRITES_PLUS 3

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES_PLUS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int w = atoi(tokens[3].c_str());
	int h = atoi(tokens[4].c_str());

	int texID = atoi(tokens[5].c_str());

	int r = l + w;
	int b = t + h;

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			//DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y, player); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;
	case OBJECT_TYPE_FLATFORM_NEN:
	{
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		int is_go_through = (float)atof(tokens[5].c_str());
		obj = new FlatForm(x, y, width, height, is_go_through);
		break;
	}
	case OBJECT_TYPE_PARA_GOOMBA:
		obj = new ParaGoomba(x, y, player);
		break;
	case OBJECT_TYPE_BRICK_COIN:
	{
		int has_item = (int)atof(tokens[3].c_str());
		obj = new BrickCoin(x, y, has_item,player);
		break;
	}
	case OBJECT_TYPE_MUSHROOM:
		obj = new Mushroom(x, y, 1);
		break;
	case OBJECT_TYPE_SUPER_LEAF:
		obj = new SuperLeaf(x, y);
		break;
	case OBJECT_TYPE_KOOPA:
	{
		int type = (int)atof(tokens[3].c_str());
		int state = (int)atof(tokens[4].c_str());
		obj = new Koopa(x, y, player,type, state);
		break;
	}
	case OBJECT_TYPE_PIPE:
	{
		int type = (int)atof(tokens[3].c_str());
		int is_can_go = (int)atof(tokens[4].c_str());
		obj = new Pipe(x, y, type, is_can_go); break;
		break;
	}
	case OBJECT_TYPE_PLANT_BULLET:
	{
		//int direction = (int)atof(tokens[3].c_str());
		//obj = new PlantBullet(x, y, p); 
		break;
	}
	case OBJECT_TYPE_VENUS_FIRE_TRAP:
	{
		int type = (int)atof(tokens[3].c_str());
		obj = new VenusFireTrap(x, y, player, type); break;
	}
	case OBJECT_TYPE_PIRANA_PLANT:
	{
		//int type = (int)atof(tokens[3].c_str());
		obj = new PiranaPlant(x, y, player); break;
	}
	case OBJECT_TYPE_BRICK_BLINK:
	{
		//int type = (int)atof(tokens[3].c_str());
		//obj = new PiranhaPlant(x, y, player); break;
		obj = new BrickBlink(x, y,player); break;
	}
	case OBJECT_TYPE_PBUTTON:
	{
		//int type = (int)atof(tokens[3].c_str());
		//obj = new PiranhaPlant(x, y, player); break;
		//obj = new BrickDebris(x, y, -1, 1.5); break;
		obj = new PButton(x, y); break;
	}
	case OBJECT_TYPE_RANDOM_BONUS:
	{
		CMario* mario = dynamic_cast<CMario*>(player);
		obj = new RandomBonus(x, y, mario); 
		break;
	}
	case OBJECT_TYPE_VIRTUAL_BOX:
	{
		//CMario* mario = dynamic_cast<CMario*>(player);
		obj = new VirtualBox(x, y, player); break;

	}
	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	if (dynamic_cast<BrickBlink*>(obj))
	{
		list_bricklink.push_back(obj);
		//DebugOut(L"[ERR]brick? : %d\n", object_type);
	}
	else
		objects.push_back(obj);

	game_ui->SetPlayer(player);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[SPRITES_PLUS]") { section = ASSETS_SECTION_SPRITES_PLUS; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case ASSETS_SECTION_SPRITES_PLUS: _ParseSection_SPRITES_PLUS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	//temp = new TextAndNumber();
	//game_time = new GameTime();

	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[MAP]") {	section = SCENE_SECTION_MAP; continue;};
		if (line == "[OBJECTS_GRID]") { section = SCENE_SECTION_OBJECTS_GRID; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
			case SCENE_SECTION_OBJECTS_GRID: _ParseSection_OBJECTS_GRID(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);

	//map = new Map(L"textures\\map_world1-1.txt", L"textures\\TileObject.png", 176, 41, 29, 30);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	if (player->GetState() == MARIO_STATE_TRANSFORM && GetTickCount64() - player->time_to_transform >= MARIO_TIME_TO_STRANSFORM && player->time_to_transform)
	{
		player->SetLevel(MARIO_LEVEL_BIG);
		player->SetState(MARIO_STATE_IDLE);
		player->time_to_transform = 0;
		//DebugOut(L"[INFO] henshin?\n");
	}

	if (player->GetState() == MARIO_STATE_TRANSFORM)
		return;

	CGame* game = CGame::GetInstance();

	//grid->GetListObjInGrid(game->GetCamX(), game->GetCamY());

	vector<LPGAMEOBJECT> coObjects;

	/*for (size_t i = 0; i < enemies.size(); i++)
		coObjects.push_back(enemies[i]);*/

	/*for (size_t i = 0; i < items.size(); i++)
		coObjects.push_back(items[i]);*/

	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		coObjects.push_back(itemsMarioCanEat[i]);
	}

	for (int i = 0; i < list_bricklink.size(); i++)
	{
		coObjects.push_back(list_bricklink[i]);
	}

	/*for (size_t i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, &coObjects);
		items[i]->is_appeared = false;*/

	/*for (size_t i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(dt, &coObjects);
		enemies[i]->is_appeared = false;

		if (dynamic_cast<BrickCoin*>(enemies[i]))*/
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
		if (dynamic_cast<BrickCoin*>(objects[i]))
		{
			BrickCoin* brick = dynamic_cast<BrickCoin*>(objects[i]);
			float x, y;
			brick->GetPosition(x, y);

			if (brick->is_hit == true && brick->dropped == false && 
				(brick->has_item == BRICKCOIN_CONTAINS_EATABLE_ITEM || brick->has_item == BRICKCOIN_CONTAINS_GREEN_MUSHROOM))
			{
				if (brick->has_item == BRICKCOIN_CONTAINS_GREEN_MUSHROOM)
				{
					Mushroom* mushroom = new Mushroom(x, y, GREEN);
					itemsMarioCanEat.push_back(mushroom);
				}
				else
				{
					if (player->GetLevel() == MARIO_LEVEL_SMALL)
					{
						Mushroom* mushroom = new Mushroom(x, y, MUSHROOM_RED);
						itemsMarioCanEat.push_back(mushroom);
					}
					else if (player->GetLevel() == MARIO_LEVEL_BIG || player->GetLevel() == MARIO_LEVEL_BIG_TAIL)
					{
						SuperLeaf* superleaf = new SuperLeaf(x, y);
						itemsMarioCanEat.push_back(superleaf);
					}
				}
				brick->dropped = true;
				player->score += SCORE;
			}
			else if (brick->is_hit == true && brick->dropped == false && brick->has_item != BRICKCOIN_CONTAINS_PBUTTON)
			{
				DebugOut(L"[clang clang]\n");
				CoinEffect* coineffect = new CoinEffect(x, y);
				itemsMarioCanEat.push_back(coineffect);

				brick->dropped = true;
				player->score += SCORE;
			}
		}
	}


	for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		itemsMarioCanEat[i]->Update(dt, &coObjects);
	}

	player->CollideWithItems(&itemsMarioCanEat);

	for (int i = 0; i < list_bricklink.size(); i++)
	{
		list_bricklink[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	//CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;

	if (cx > END_FIRST_SCENE) cx = END_FIRST_SCENE - END_FIRST_SCENE_GAP;

	if (player->y < TOP_IN_GROUND) //in the sky
	{
		CGame::GetInstance()->SetCamPos(cx, 0);
	}
	else if (player->GetY() >= TOP_IN_GROUND && player->GetY() <= BOT_IN_GROUND)
	{
		CGame::GetInstance()->SetCamPos(cx, CAM_Y_IN_GROUND);
		//grid->UpdatePositionInGrid(game->GetCamX(), CAM_Y_IN_GROUND);
	}

	else if (player->GetY() > BOT_IN_GROUND)
	{
		CGame::GetInstance()->SetCamPos(cx, BOT_IN_GROUND);
		//grid->UpdatePositionInGrid(game->GetCamX(), BOT_IN_GROUND);
	}

	//CGame::GetInstance()->SetCamPos(cx, 700.0f);

	PurgeDeletedObjects();

	//game_time->Update(dt);
	//DebugOut(L"[INFO] game time value is: %d\n", game_time->gameTime);
}

void CPlayScene::Render()
{
	map->Draw();

	for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		itemsMarioCanEat[i]->Render();
	}

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	/*for (int i = 0; i < items.size(); i++)
		items[i]->Render();*/

	/*for (int i = 0; i < enemies.size(); i++)
		enemies[i]->Render();*/

	for (int i = 0; i < list_bricklink.size(); i++)
	{
		list_bricklink[i]->Render();
	}

	//game_time = GameTime::GetInstance();
	//temp.Render(100, 800, temp.FillZeroString(to_string(15 - game_time->gameTime), 5));
	//game_ui->Render(GAME_TIME  /*- game_time->GetTime()*/, player->hit_brick_number, player->score, LIFE, SCENE);
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);
	DebugOut(L"[INFO] play scene mapid loading scene resources from : %s \n", line);

	if (tokens.size() < 5) return;

	/*map->LoadMap(atoi(tokens[0].c_str()),
		ToLPCWSTR(tokens[1]), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()),
		ToLPCWSTR(tokens[4]), atoi(tokens[5].c_str()), atoi(tokens[6].c_str()));*/

	map = new Map(ToLPCWSTR(tokens[0]), ToLPCWSTR(tokens[1]), atoi(tokens[2].c_str()), atoi(tokens[3].c_str()), atoi(tokens[4].c_str()), atoi(tokens[5].c_str()));
	//map = new Map(L"textures\\map_world1-1.txt", L"textures\\TileObject.png", 176, 41, 29, 30);


	map->LoadTileSet();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	for (int i = 0; i < itemsMarioCanEat.size(); i++)
		delete itemsMarioCanEat[i];

	for (int i = 0; i < list_bricklink.size(); i++)
		delete list_bricklink[i];

	objects.clear();
	itemsMarioCanEat.clear();
	list_bricklink.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::DropItem(int itemType, float x, float y)
{
	switch (itemType)
	{
	case 4:
	{
		/*if (player->GetLevel() == MARIO_LEVEL_SMALL)
		{
			Mushroom* mushroom = new Mushroom(x, y);
			if (player->y < 567)
				mushroom->is_read_mushroom = false;
			itemsMarioCanEat.push_back(mushroom);
		}
		else if (player->GetLevel() == MARIO_LEVEL_BIG || player->GetLevel() == MARIO_LEVEL_BIG_TAIL)
		{
			SuperLeaf* superleaf = new SuperLeaf(x, y);
			itemsMarioCanEat.push_back(superleaf);
		}
		break;*/
	}
	}
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::_ParseSection_OBJECTS_GRID(string line)
{
	//DebugOut(L"hello object grid\n");
	DebugOut(L"[INFO] object grid : %s \n", line);

	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines
	wstring objPath = ToWSTR(tokens[0].c_str());
	wstring gridPath = ToWSTR(tokens[1].c_str());

	/*grid = new CGrid(objPath.c_str(), gridPath.c_str(), player);
	grid->ReadFileObj();
	grid->ReadFileGrid();*/
}

void CPlayScene::PurgeDeletedObjects()
{
	/*for (size_t i = 0; i < items.size(); i++)
	{
		if (items[i]->IsDeleted() == true)
		{
			delete items[i];
			items[i] = nullptr;
			items.erase(items.begin() + i);
		}
	}*/

	/*for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsDeleted() == true)
		{
			delete enemies[i];
			enemies[i] = nullptr;

			enemies.erase(enemies.begin() + i);
		}
	}*/

	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	for (size_t i = 0; i < itemsMarioCanEat.size(); i++)
	{
		if (itemsMarioCanEat[i]->IsDeleted() == true)
		{
			delete itemsMarioCanEat[i];
			itemsMarioCanEat[i] = nullptr;
			//DebugOut(L"hihihi, delete roi ne\n");
			itemsMarioCanEat.erase(itemsMarioCanEat.begin() + i);
		}
	}

	for (int i = 0; i < list_bricklink.size(); i++)
	{
		if (list_bricklink[i]->IsDeleted())
		{
			delete list_bricklink[i];
			list_bricklink[i] = nullptr;

			list_bricklink.erase(list_bricklink.begin() + i);
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}