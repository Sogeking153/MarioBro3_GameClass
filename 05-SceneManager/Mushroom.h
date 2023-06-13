#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

//#define	COIN_WIDTH 10
#define MUSH_ROOM_BBOX_WIDTH  48
#define MUSH_ROOM_BBOX_HEIGHT  48

#define  MUSHROOM_STATE_GOING_UP		 100
#define  MUSHROOM_STATE_MOVING_LEFT		 200
#define  MUSHROOM_STATE_MOVING_RIGHT	 300

#define  MUSHROOM_DISTANCE_MOVE_UP	 55

#define  MUSHROOM_MOVING_SPEED	 0.1

#define  ANI_MUSHROOM_RED			7004
#define  ANI_MUSHROOM_GREEN			762

#define MUSHROOM_RED		1
#define MUSHROOM_GREEN 		2

#define AY_MUSHROOM 0.002
#define VY_MUSHROOM_GO_UP 0.1f

class Mushroom : public CGameObject {
	float ax;
	float ay;
public:
	int type = MUSHROOM_RED;
	float pos_y_brick = y;
	bool enable_gravity = false;
	Mushroom(float x, float y, int type);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; };
	int IsCollidable() { return 1; };

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnNoCollision(DWORD dt);
	virtual void SetState(int state);
};

