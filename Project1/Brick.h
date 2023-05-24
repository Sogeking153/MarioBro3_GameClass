#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "BrickDebris.h"

#define ID_ANI_BRICK 10000
#define ID_ANI_DEBRIS_BRICK 10001
#define BRICK_WIDTH 48
#define BRICK_BBOX_WIDTH 48
#define BRICK_BBOX_HEIGHT 48
#define BRICK_BLINK_STATE_IS_HIT 100
#define DEBRIS_DISTANCE 9
#define BRICK_BLINK_STATE_COIN 200
#define ID_ANI_COIN_STAND_STILL 10020

class CBrick : public CGameObject {
public:
	bool is_block = true;
	vector<LPGAMEOBJECT> vec_debris;

	bool is_hit = false;

	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	virtual int IsBlocking() { return is_block; }

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//int IsBlocking() { return 0; }
};