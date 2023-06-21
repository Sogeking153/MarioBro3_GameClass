#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Game.h"

#define STATE_GHOST_PLATFORM 0
#define STATE_CACTUS 1
#define STATE_HELP_TAG 2
#define STATE_GUARD 3
#define STATE_3_INTRO 4
#define STATE_ARROW 5

#define ANI_GHOST_PLATFORM 0
#define ANI_CACTUS 759
#define ANI_HELP_TAG 760
#define ANI_GUARD_RIGHT 761
#define ANI_GUARD_LEFT 7761
#define ANI_3_INTRO 4
#define ANI_ARROW 5

#define LEFT_GUARD 250
#define RIGHT_GUARD 336
#define VX_GUARD 0.05

class VisibleObject : public CGameObject
{
public:
	int w;
	int h;
	VisibleObject(float x, float y, float width, float height, int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
};