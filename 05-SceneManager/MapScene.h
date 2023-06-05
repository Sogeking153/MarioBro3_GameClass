#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "TextAndNumber.h"
#include "GameTime.h"
#include "ParaGoomba.h"
#include "Map.h"
#include "PiranaPlant.h"

class MapScene : public CScene
{
public:
	Map* map;

	CMario* player;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_SPRITES_PLUS(string line);

	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	//public: 
	MapScene(int id, LPCWSTR filePath);

	virtual void Load(); //load file scene 02, 01
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef MapScene* LPMAPSCENE;