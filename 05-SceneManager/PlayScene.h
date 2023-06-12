#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "TextAndNumber.h"
#include "GameTime.h"
#include "Map.h"
#include "PiranaPlant.h"
#include "UI.h"
#include "CoinEffect.h"
#include "Grid.h"
//#include "Koopas.h"

class CPlayScene: public CScene
{
public: 
	// A play scene has to have player, right? 
	CGrid* grid;

	//GameTime* game_time;
	UI* game_ui;

	Map* map;
	//LPGAMEOBJECT player;	
	CMario* player;
	TextAndNumber temp;

	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> list_bricklink;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> itemsMarioCanEat;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_OBJECTS_GRID(string line);

	void LoadAssets(LPCWSTR assetFile);
	
//public: 
	void DropItem(int itemType, float x, float y);
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	void SetEnemiesInScene(vector<LPGAMEOBJECT> listEnemy) { enemies.clear(); enemies = listEnemy; }
};

typedef CPlayScene* LPPLAYSCENE;

