#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlantBullet.h"

#define VENUS_WALKING_SPEED 0.06f;

#define PIRANA_PLANT_BBOX_WIDTH  16*3
#define PIRANA_PLANT_BBOX_HEIGHT  28*3

#define GREEN_BBOX_HEIGHT 27*3

#define VENUS_STATE_GOING_UP			 100
#define VENUS_STATE_GOING_DOWN			 200
#define VENUS_STATE_SHOOTING_UP			 300
#define VENUS_STATE_SHOOTING_DOWN		 400
#define VENUS_STATE_SEEING				 500
#define VENUS_STATE_STANDING_STILL		 600
#define VENUS_STATE_SLEEPING	700

//#define GOOMBA_BBOX_HEIGHT_DIE 9

#define ANI_PIRANA_PLANT 744
#define PIRANA_WIDTH_SAFE 90

#define TIME_TO_GO_UP 2000
#define TIME_TO_GO_DOWN 5000

#define GAP_MIN_Y 7
#define GAP_MAX_Y 10

class PiranaPlant : public CGameObject
{
protected:


	float l_safe;
	float t_safe;
	float r_safe;
	float b_safe;

	float min_y = y;
	float max_y = y;


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
	PiranaPlant(float x, float y, LPGAMEOBJECT mario);
	virtual void SetState(int state);


};

