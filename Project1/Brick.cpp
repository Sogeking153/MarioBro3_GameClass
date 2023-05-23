#include "Brick.h"
#include "debug.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == BRICK_BLINK_STATE_IS_HIT)
		//animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	{
		vec_debris[0]->Render();
		return;
	}

	animations->Get(10001)->Render(x, y);

	DebugOut(L"[INFO] brick state %d\n", state);

	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < vec_debris.size(); i++)
	{
		vec_debris[i]->Update(dt);
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (is_hit == true)
		return;
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state)
{
	switch (state)
	{
	case BRICK_BLINK_STATE_IS_HIT:
		BrickDebris* debrick_brick = NULL;
		debrick_brick = new BrickDebris(this->x, this->y - 40, 1, 1.5);
		vec_debris.push_back(debrick_brick);
		break;
	}
	CGameObject::SetState(state);
}