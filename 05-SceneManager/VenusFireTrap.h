#pragma once
#include "GameObject.h"
#include "Mario.h"

#define VENUS_WALKING_SPEED 0.06f;

#define VENUS_BBOX_WIDTH 16*3
#define VENUS_BBOX_HEIGHT 32*3

#define GOOMBA_BBOX_HEIGHT_DIE 9

#define VENUS_STATE_GOING_UP			 100
#define VENUS_STATE_GOING_DOWN			 200
#define VENUS_STATE_SHOOTING_UP			 300
#define VENUS_STATE_SHOOTING_DOWN		 400
#define VENUS_STATE_SEEING				 500
#define VENUS_STATE_STANDING_STILL		 600
#define VENUS_STATE_SLEEPING			700

#define VENUS_ANI_SCORPION_DOWN_LEFT 725
#define VENUS_ANI_SCORPION_UP_LEFT 726
#define VENUS_ANI_SHOOTING_DOWN_LEFT 727
#define VENUS_ANI_SHOOTING_UP_LEFT 728

#define GREEN_ANI_SCORPION_DOWN_LEFT 729
#define GREEN_ANI_SCORPION_UP_LEFT 730
#define GREEN_ANI_SHOOTING_DOWN_LEFT 731
#define GREEN_ANI_SHOOTING_UP_LEFT 732

#define VENUS_ANI_SCORPION_DOWN_RIGHT 825
#define VENUS_ANI_SCORPION_UP_RIGHT 826
#define VENUS_ANI_SHOOTING_DOWN_RIGHT 827
#define VENUS_ANI_SHOOTING_UP_RIGHT 828

#define GREEN_ANI_SCORPION_DOWN_RIGHT 829
#define GREEN_ANI_SCORPION_UP_RIGHT 830
#define GREEN_ANI_SHOOTING_DOWN_RIGHT 831
#define GREEN_ANI_SHOOTING_UP__RIGHT7 832

class VenusFireTrap : public CGameObject
{
protected:
	float origin_y = y;
	ULONGLONG time_interval;

	float ax;
	float ay;
	LPGAMEOBJECT player;
	ULONGLONG die_start;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	VenusFireTrap(float x, float y, LPGAMEOBJECT mario);
	virtual void SetState(int state);
};

