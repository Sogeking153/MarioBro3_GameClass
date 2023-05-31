#pragma once
#include "GameObject.h"
#include "Mario.h"

#define	 PIPE_TALL_BBOX_WIDTH 32*3
#define	 PIPE_TALL_BBOX_HEIGHT 48*3
#define	 PIPE_SHORT_BBOX_WIDTH 32*3
#define	 PIPE_SHORT_BBOX_HEIGHT 32*3

#define  PIPE_STATE_TALL				100
#define  PIPE_STATE_SHORT				200
#define  PIPE_STATE_BLACK				300

#define  ANI_PIPE_TALL				740
#define  ANI_PIPE_SHORT				741
#define  ANI_PIPE_BLACK				742

class Pipe : public CGameObject
{
protected:

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 0; }
	//virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	Pipe(float x, float y) { SetState(PIPE_STATE_TALL); };
	virtual void SetState(int state);
};