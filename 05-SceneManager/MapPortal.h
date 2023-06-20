#pragma once
#include "Mario.h"
#include "Game.h"

#define STATE_START 0
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3
#define STATE_4 4
#define STATE_5 5
#define STATE_6 6
#define STATE_CARD 7
#define STATE_EMPTY 8

#define ANI_START 0
#define ANI_1 1
#define ANI_2 2
#define ANI_3 3
#define ANI_4 4
#define ANI_5 5
#define ANI_6 6
#define ANI_CARD 7
#define ANI_EMPTY 8

#define MAP_PORTAL_BBOX_WIDTH  16*3
#define MAP_PORTAL_BBOX_HEIGHT 16*3


class MapPortal : public CGameObject
{
public:
	int t, l, r, b;
	int id_portal;
	int is_portal;

	MapPortal(int id, float x, float y, bool is_portal, int t, int r, int b, int l, int state);
	~MapPortal() {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) {};
	void Render();


};