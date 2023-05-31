#pragma once
#include "GameObject.h"
#include "Mario.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f

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

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define VENUS_ANI_SCORPION_DOWN_LEFT 725
#define VENUS_ANI_SCORPION_UP_LEFT 726
#define VENUS_ANI_SHOOTING_DOWN_LEFT 727
#define VENUS_ANI_SHOOTING_UP_LEFT 728

#define VENUS_GREEN_ANI_SCORPION_DOWN_LEFT 729
#define VENUS_GREEN_ANI_SCORPION_UP_LEFT 730
#define VENUS_GREEN_ANI_SHOOTING_DOWN_LEFT 731
#define VENUS_GREEN_ANI_SHOOTING_UP_LEFT 732

#define VENUS_ANI_SCORPION_DOWN_RIGHT 825
#define VENUS_ANI_SCORPION_UP_RIGHT 826
#define VENUS_ANI_SHOOTING_DOWN_RIGHT 827
#define VENUS_ANI_SHOOTING_UP_RIGHT 828

#define VENUS_GREEN_ANI_SCORPION_DOWN_RIGHT 829
#define VENUS_GREEN_ANI_SCORPION_UP_RIGHT 830
#define VENUS_GREEN_ANI_SHOOTING_DOWN_RIGHT 831
#define VENUS_GREEN_ANI_SHOOTING_UP__RIGHT7 832

class VenusFireTrap : public CGameObject
{
protected:
	float ax;
	float ay;
	LPGAMEOBJECT player;
	ULONGLONG die_start;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	VenusFireTrap(float x, float y, LPGAMEOBJECT mario);
	virtual void SetState(int state);
};

