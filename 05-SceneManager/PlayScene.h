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
//#include "Koopas.h"

class CPlayScene: public CScene
{
public: 
	// A play scene has to have player, right? 
	Map* map;
	//LPGAMEOBJECT player;	
	CMario* player;
	TextAndNumber temp;
	GameTime* game_time;

	vector<LPGAMEOBJECT> list_bricklink;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> itemsMarioCanEat;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

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
};

typedef CPlayScene* LPPLAYSCENE;

