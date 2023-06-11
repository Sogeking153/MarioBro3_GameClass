#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "MoneyEffect.h"

#define GOOMBA_GRAVITY 0.002f
#define PARAGOOMBA_WALKING_SPEED 0.06f
#define PARAGOOMBA_VY_SHORT_JUMP 0.25*1.5
#define PARAGOOMBA_VY_HIGH_JUMP  0.25*3.5
#define PARAGOOMBA_VY_BEING_SHOOT 0.25*3.5
#define PARAGOOMBA_VX_BEING_SHOOT 0.1

#define GOOMBA_BBOX_WIDTH 16*3
#define GOOMBA_BBOX_HEIGHT 14*3
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define PARA_GOOMBA_STATE_WALKING		100
#define PARA_GOOMBA_STATE_DIE			200
#define PARA_GOOMBA_STATE_JUMP_SHORT_1	300
#define PARA_GOOMBA_STATE_JUMP_SHORT_2	400
#define PARA_GOOMBA_STATE_JUMP_SHORT_3	500
#define PARA_GOOMBA_STATE_JUMP_HIGH		600
#define PARA_GOOMBA_STATE_WALKING_RIGHT		700
#define PARA_GOOMBA_STATE_WALKING_LEFT		800
#define PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING		900
#define PARA_GOOMBA_STATE_WAS_SHOOTED		1000

#define ID_ANI_PARA_GOOMBA_WALKING 5020
#define ID_ANI_PARA_GOOMBA_JUMP_SMALL 5021
#define ID_ANI_PARA_GOOMBA_JUMP_BIG 5022
#define ID_ANI_PARA_GOOMBA_WITHOUT_SWING 5023
#define ID_ANI_PARA_GOOMBA_DIE 5024
#define ID_ANI_PARA_GOOMBA_WAS_SHOOTED 5401

#define TIME_WALKING 2000

class ParaGoomba : public CGameObject
{
protected:
	MoneyEffect* effect = NULL;
	int is_minus_vx = false;
	int is_colliable = 1;
	int count = 0;
	float ax;
	float ay;
	CMario* player;
	ULONGLONG die_start;

	ULONGLONG walking_start = 0;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return is_colliable; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	ParaGoomba(float x, float y, LPGAMEOBJECT mario);
	virtual void SetState(int state);
};

