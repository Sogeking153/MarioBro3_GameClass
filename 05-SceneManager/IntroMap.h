#pragma once
#include "Map.h"
#include "Game.h"
#include "Mario.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"

#define POS_CAM_X_2 -20
#define POS_CAM_Y_2 -50

class IntroMap : public CScene
{
public:
	Map* map_1 = NULL;
	Map* map_2 = NULL;
	Map* map_3 = NULL;
	Map* map_4 = NULL;
	Map* map_5 = NULL;
	Map* map_6 = NULL;
	CMario* player;
	vector<LPGAMEOBJECT> objects;

	IntroMap(int id, LPCWSTR filePath);

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP_1(string line);
	void _ParseSection_MAP_2(string line);
	void _ParseSection_MAP_3(string line);
	void _ParseSection_MAP_4(string line);
	void _ParseSection_MAP_5(string line);
	void _ParseSection_MAP_6(string line);
	void LoadAssets(LPCWSTR assetFile);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void Clear();
	void PurgeDeletedObjects();

	LPGAMEOBJECT GetPlayer() { return player; }

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef IntroMap* LPINTROMAP;