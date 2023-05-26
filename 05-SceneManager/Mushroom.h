#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 48
#define COIN_BBOX_HEIGHT 48

#define MUSHROOM_STATE_WALKING		100

class Mushroom : public CGameObject {
	float ax;
	float ay;
public:
	Mushroom(float x, float y) : CGameObject(x, y) { SetState(MUSHROOM_STATE_WALKING); }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; };
	int IsCollidable() { return 1; };

	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
};

