#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 48
#define BRICK_BBOX_WIDTH 2000
#define BRICK_BBOX_HEIGHT 8

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//int IsBlocking() { return 0; }
};