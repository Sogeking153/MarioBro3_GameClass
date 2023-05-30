#include "Mushroom.h"

void Mushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	animations->Get(724)->Render(x, y);

	/*animations->Get(720)->Render(x+50, y);
	animations->Get(722)->Render(x+100, y);
	animations->Get(723)->Render(x+150, y);
	animations->Get(746)->Render(x+200, y);
	animations->Get(747)->Render(x+250, y);
	animations->Get(748)->Render(x+300, y);*/

	RenderBoundingBox();
}

void Mushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (enable_gravity == true)
		vy += 0.0002 * dt;

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
	if (state == MUSHROOM_STATE_GOING_UP)
	{
		y += vy * dt;
		if (y <= pos_y_brick - MUSHROOM_DISTANCE_MOVE_UP)
		{
			SetState(MUSHROOM_STATE_MOVING_RIGHT);
		}
	}

	if (state == MUSHROOM_STATE_MOVING_RIGHT)
	{
		x += vx * dt;
		y += vy * dt;
	}
}

void Mushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_GOING_UP:
		vx = 0;
		vy = -0.1f;
		break;
	case MUSHROOM_STATE_MOVING_LEFT:
		vx = -MUSHROOM_MOVING_SPEED;
		vy = 0;
		enable_gravity = true;
		//vx = 0;
		break;
	case MUSHROOM_STATE_MOVING_RIGHT:
		vx = MUSHROOM_MOVING_SPEED;
		vy = 0;
		enable_gravity = true;
		//vy = 0.5;
		break;
	}
}