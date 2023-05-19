#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.02f


#define GOOMBA_BBOX_WIDTH 16*3
#define GOOMBA_BBOX_HEIGHT 27*3
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_BBOX_WIDTH_INDENT_IN 16*3
#define GOOMBA_BBOX_HEIGHT_INDENT_IN 16*3

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_INDENT_IN 300
#define GOOMBA_STATE_SHELL_RUNNING 400
#define GOOMBA_STATE_BEING_HOLDED 500

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define ID_ANI_KOOPA_WALKING_LEFT 6000
#define ID_ANI_KOOPA_INDENT_IN 6100

class Koopa : public CGameObject
{
protected:
	float ax = 0;
	float ay = 0;
	CMario* player;
	ULONGLONG die_start;


	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Koopa(float x, float y, CMario* mario);
	virtual void SetState(int state);
};

