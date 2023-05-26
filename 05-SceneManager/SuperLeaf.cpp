#include "SuperLeaf.h"

void SuperLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(722)->Render(x, y);
	RenderBoundingBox();
}

void SuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	//x += vx*dt;
}

void SuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void SuperLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case SUPERLEAF_STATE_WALKING:
		vy = 0.02;
		//vx = 0;
		break;
	}
}
