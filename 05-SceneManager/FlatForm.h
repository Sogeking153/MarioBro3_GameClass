#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 48
#define BRICK_BBOX_WIDTH 2000
#define BRICK_BBOX_HEIGHT 8

class FlatForm : public CGameObject {
public:

	float width;
	float height;
	FlatForm(float x, float y, float w, float h) : CGameObject(x, y) { width = w; height = h; }
	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 1; }
	//int IsBlocking() { return 0; }
};

