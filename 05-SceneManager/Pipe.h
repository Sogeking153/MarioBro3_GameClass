#pragma once
#include "GameObject.h"
#include "Mario.h"

#define	 PIPE_TALL_BBOX_WIDTH 32*3
#define	 PIPE_TALL_BBOX_HEIGHT 48*3
#define	 PIPE_SHORT_BBOX_WIDTH 30*3
#define	 PIPE_SHORT_BBOX_HEIGHT 32*3

#define  PIPE_STATE_TALL				100
#define  PIPE_STATE_SHORT				200
#define  PIPE_STATE_BLACK				300

#define  ANI_PIPE_TALL				740
#define  ANI_PIPE_SHORT				741
#define  ANI_PIPE_BLACK				742

class Pipe : public CGameObject
{
public:
	bool is_pine_can_go = false;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Pipe(float x, float y, int type, int is_pine_can_go);
	virtual void SetState(int state);
};