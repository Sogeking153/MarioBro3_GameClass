#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define  DEBRIS_BRICK_GRAVITY		0.0009
#define  DEBRIS_BRICK_SPEED_X		0.07
#define  DEBRIS_BRICK_SPEED_Y		0.26

#define ID_ANI_DEBRIS_BRICK 10001

class BrickDebris :public CGameObject
{
public:

	BrickDebris(float brick_pos_x, float brick_pos_y, int nx, float height);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};


};

