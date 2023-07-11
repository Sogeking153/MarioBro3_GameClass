#pragma once
#include "GameObject.h"
#include "Mario.h"

#define PLANT_BULLET_WALKING_SPEED 0.15f;

#define PLANT_BULLET_BBOX_WIDTH 9*3
#define PLANT_BULLET_BBOX_HEIGHT 9*3
#define PLANT_BULLET_BBOX_HEIGHT_DIE 9

//7 8 10 11 - 1 2 4 5

#define PLANT_BULLET_STATE_BOT_LEFT_NEAR 500
#define PLANT_BULLET_STATE_TOP_LEFT_NEAR 600
#define PLANT_BULLET_STATE_BOT_LEFT_FAR 700
#define PLANT_BULLET_STATE_TOP_LEFT_FAR 800

#define PLANT_BULLET_STATE_TOP_RIGHT_NEAR 100 //started clockwise at 12 o'clock
#define PLANT_BULLET_STATE_BOT_RIGHT_NEAR 200
#define PLANT_BULLET_STATE_TOP_RIGHT_FAR 300
#define PLANT_BULLET_STATE_BOT_RIGHT_FAR 400

#define ANI_PLANT_BULLET 704

class PlantBullet : public CGameObject
{
protected:
	bool is_hit_mario = false;
	LPGAMEOBJECT player;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	PlantBullet(float x, float y, LPGAMEOBJECT player);
	virtual void SetState(int state);
};

