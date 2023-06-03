#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.04f


#define GOOMBA_BBOX_WIDTH 16*3
#define GOOMBA_BBOX_HEIGHT 14*3
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING		100
#define GOOMBA_STATE_DIE			200
#define GOOMBA_STATE_JUMP_SHORT_1	300
#define GOOMBA_STATE_JUMP_SHORT_2	400
#define GOOMBA_STATE_JUMP_SHORT_3	500
#define GOOMBA_STATE_JUMP_HIGH		600
#define GOOMBA_STATE_WALKING_RIGHT		700
#define GOOMBA_STATE_WALKING_LEFT		800
#define GOOMBA_STATE_WALKING_WITHOUT_SWING		900
#define GOOMBA_STATE_WAS_SHOOTED			1000

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

class CGoomba : public CGameObject
{
public:
	bool is_minus_vx = false;
	bool is_colliable = 1;
	float ax;				
	float ay; 

	LPGAMEOBJECT player;
	ULONGLONG die_start;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return is_colliable; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CGoomba(float x, float y, LPGAMEOBJECT mario);
	virtual void SetState(int state);
};