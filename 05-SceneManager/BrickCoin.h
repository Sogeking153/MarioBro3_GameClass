#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_COIN 10000
#define BRICK_COIN_WIDTH 48
#define BRICK_COIN_BBOX_WIDTH 48
#define BRICK_COIN_BBOX_HEIGHT 48

#define BRICK_COIN_STATE_NOT_HIT	100
#define BRICK_COIN_STATE_HIT 		200
#define BRICK_COIN_STATE_BOUCING 	300

#define ID_ANI_BRICK_QUESION		702
#define ID_ANI_BRICK_QUESION_IS_HIT 720

class BrickCoin : public CGameObject {
public:
	bool dropped = false;
	bool is_hit = false;
	bool flag = false;
	float originalY = y;
	BrickCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

