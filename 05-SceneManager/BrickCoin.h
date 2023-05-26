#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_COIN 10000
#define BRICK_COIN_WIDTH 48
#define BRICK_COIN_BBOX_WIDTH 48
#define BRICK_COIN_BBOX_HEIGHT 48

class BrickCoin : public CGameObject {
public:
	BrickCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

