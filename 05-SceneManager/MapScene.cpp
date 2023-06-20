#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "MapScene.h"
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
#include "Pipe.h"
#include "PlantBullet.h"
#include "VenusFireTrap.h"
#include "BrickBlink.h"
#include "BrickDebris.h"
#include "PButton.h"
#include "RandomBonus.h"
#include "Koopa.h"
#include "MapPortal.h"

#include "SampleKeyEventHandler.h"

using namespace std;

MapScene::MapScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new MapSceneKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2
#define ASSETS_SECTION_SPRITES_PLUS 3
#define SCENE_SECTION_MAP_SELECTION 7

#define MAX_SCENE_LINE 1024

void MapScene::_ParseSection_SPRITES(string line)
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

void MapScene::_ParseSection_SPRITES_PLUS(string line)
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

void MapScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void MapScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void MapScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		int is_in_world_map = atoi(tokens[3].c_str());

		obj = new CMario(x, y, is_in_world_map);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	}
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
	case 7: obj = new ParaGoomba(x, y, player); break;
	case 8:
	{
		int has_item = (int)atof(tokens[3].c_str());
		obj = new BrickCoin(x, y, has_item,player); break;
	}
	case 9: obj = new Mushroom(x, y,1); break;
	case 10: obj = new SuperLeaf(x, y); break;
	case 11:
	{
		int type = (int)atof(tokens[3].c_str());
		int state = (int)atof(tokens[4].c_str());

		obj = new Koopa(x, y, player, type, state); break;
	}
	case 12:
	{
		int type = (int)atof(tokens[3].c_str());
		int is_can_go = (int)atof(tokens[4].c_str());
		obj = new Pipe(x, y, type, is_can_go); 
		break;
	}
	case 13:
	{
		//int direction= (int)atof(tokens[3].c_str());
		//obj = new PlantBullet(x, y,p); break;
	}
	case 14:
	{
		int type = (int)atof(tokens[3].c_str());
		obj = new VenusFireTrap(x, y, player, type); break;
	}
	case 15:
	{
		//int type = (int)atof(tokens[3].c_str());
		obj = new PiranaPlant(x, y, player); break;
	}
	case 16:
	{
		//int type = (int)atof(tokens[3].c_str());
		//obj = new PiranhaPlant(x, y, player); break;
		obj = new BrickBlink(x, y,player); break;
	}
	case 17:
	{
		//int type = (int)atof(tokens[3].c_str());
		//obj = new PiranhaPlant(x, y, player); break;
		//obj = new BrickDebris(x, y, -1, 1.5); break;

		obj = new PButton(x, y); break;

	}
	case 18:
	{
		CMario* mario = dynamic_cast<CMario*>(player);
		obj = new RandomBonus(x, y, mario); break;

	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	//if (dynamic_cast<BrickBlink*>(obj))
	//{
		//list_bricklink.push_back(obj);
		
	//}
	//else

	objects.push_back(obj);
}

void MapScene::_ParseSection_MAP_SELECTION(string line)
{
	vector<string> tokens = split(line);
	if (tokens.size() < 9) return;

	int id = atof(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	int is_portal = atof(tokens[3].c_str());
	int t = atof(tokens[4].c_str());

	int r = atoi(tokens[5].c_str());
	int b = atoi(tokens[6].c_str());
	int l = atoi(tokens[7].c_str());
	int state = atoi(tokens[8].c_str());

	CGameObject* obj = new MapPortal(id, x, y, is_portal, t, r, b, l, state);

	map_portals.push_back(obj);
}

void MapScene::LoadAssets(LPCWSTR assetFile)
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
		//ASSETS_SECTION_SPRITES_PLUS
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

void MapScene::Load()
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
		if (line == "[MAP_SELECTION]") { section = SCENE_SECTION_MAP_SELECTION; continue; }
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP_SELECTION: _ParseSection_MAP_SELECTION(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);

	//0	textures\world_map.txt	12	16	textures\tileset_worldmap.png	4 	8
	map = new Map(L"textures\\world_map.txt", L"textures\\tileset_worldmap.png", 16, 12, 8, 4);
	map->LoadTileSet();

	current_portal = dynamic_cast<MapPortal*>(map_portals[0]);
}

void MapScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	/*for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		coObjects.push_back(itemsMarioCanEat[i]);
	}
	for (int i = 0; i < list_bricklink.size(); i++)
	{
		coObjects.push_back(list_bricklink[i]);
	}*/



	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);

		/*if (dynamic_cast<BrickCoin*>(objects[i]))
		{
			BrickCoin* brick = dynamic_cast<BrickCoin*>(objects[i]);
			if (brick->is_hit == true && brick->dropped == false && brick->has_item == BRICKCOIN_CONTAINS_EATABLE_ITEM)
			{
				DebugOut(L"[INFO] what type is it? %d\n", brick->has_item);
				float x, y;
				brick->GetPosition(x, y);
				if (player->GetLevel() == MARIO_LEVEL_SMALL)
				{
					Mushroom* mushroom = new Mushroom(x, y);
					itemsMarioCanEat.push_back(mushroom);
				}
				else if (player->GetLevel() == MARIO_LEVEL_BIG || player->GetLevel() == MARIO_LEVEL_BIG_TAIL || player->GetLevel() == MARIO_LEVEL_BIG_ORANGE)
				{
					SuperLeaf* superleaf = new SuperLeaf(x, y);
					itemsMarioCanEat.push_back(superleaf);
				}
				brick->dropped = true;
			}
		}*/
	}

	/*for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		itemsMarioCanEat[i]->Update(dt, &coObjects);
	}
	for (int i = 0; i < list_bricklink.size(); i++)
	{
		list_bricklink[i]->Update(dt, &coObjects);
	}*/

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	//if (cx < 0) cx = 0;
	//if (cx > 8448 - 760) cx = 8448 - 760 - 10;
	//CGame::GetInstance()->SetCamPos(cx, 700);

	/*if (player->GetY() > 1368)
		CGame::GetInstance()->SetCamPos(cx, 1365);
	else*/
		CGame::GetInstance()->SetCamPos(POS_CAM_X, POS_CAM_Y);

	PurgeDeletedObjects();


	//game_time->Update(dt);
	//	DebugOut(L"[INFO] game time is: %d\n", game_time->gameTime);
}

void MapScene::Render()
{
	map->Draw();

	for (size_t i = 0; i < map_portals.size(); i++)
	{
		map_portals[i]->Render();
	}

	/*for (int i = 0; i < itemsMarioCanEat.size(); i++)
	{
		itemsMarioCanEat[i]->Render();
	}*/

	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();

	/*for (int i = 0; i < list_bricklink.size(); i++)
	{
		list_bricklink[i]->Render();
	}
	temp.Render(100, 800, temp.FillZeroString(to_string(15 - game_time->gameTime), 5));
	*/
}

/*
*	Clear all objects from this scene
*/
void MapScene::Clear()
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
void MapScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	for (int i = 0; i < map_portals.size(); i++)
		delete map_portals[i];
	map_portals.clear();

	for (int i = 0; i < map_portals.size(); i++)
		delete map_portals[i];
	map_portals.clear();

	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool MapScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void MapScene::PurgeDeletedObjects()
{
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

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), MapScene::IsGameObjectDeleted),
		objects.end());
}