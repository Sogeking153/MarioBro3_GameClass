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

class CBrick : public CGameObject {
public:
	vector<LPGAMEOBJECT> vec_debris;

	bool is_hit = false;

	CBrick(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//int IsBlocking() { return 0; }
};