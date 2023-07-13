#pragma once
#include "Map.h"
#include "Game.h"
#include "Mario.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"

class IntroMap : public CScene
{
public:
	Map* map = NULL;
	CMario* player;
	vector<LPGAMEOBJECT> objects;

	IntroMap(int id, LPCWSTR filePath);

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
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