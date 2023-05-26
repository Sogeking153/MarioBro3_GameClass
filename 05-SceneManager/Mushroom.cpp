#include "Mushroom.h"

void Mushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	animations->Get(724)->Render(x, y);

	animations->Get(720)->Render(x+50, y);
	animations->Get(722)->Render(x+100, y);
	animations->Get(723)->Render(x+150, y);
	animations->Get(746)->Render(x+200, y);
	animations->Get(747)->Render(x+250, y);
	animations->Get(748)->Render(x+300, y);

	RenderBoundingBox();
}

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += 0.0002 * dt;
	//vx += ax * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Mushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void Mushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Mushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_WALKING:
		vx = -0.02;
		//vx = 0;
		break;
	}
}