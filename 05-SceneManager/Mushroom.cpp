#include "Mushroom.h"

Mushroom::Mushroom(float x, float y, int type) : CGameObject(x, y)
{
	SetState(MUSHROOM_STATE_GOING_UP);

	/*if (y < 600)
		type = GREEN;*/
	this->type = type;

}

void Mushroom::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int IdAni = ANI_MUSHROOM_RED;

	if (type == MUSHROOM_GREEN)
		IdAni = ANI_MUSHROOM_GREEN;

	animations->Get(IdAni)->Render(x, y);

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
		vy += AY_MUSHROOM * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);

	this->DeleteWhenOutOfCam();
}

void Mushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - MUSH_ROOM_BBOX_WIDTH / 2;
	t = y - MUSH_ROOM_BBOX_HEIGHT / 2;
	r = l + MUSH_ROOM_BBOX_WIDTH;
	b = t + MUSH_ROOM_BBOX_HEIGHT;
}

void Mushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
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
		vy = -VY_MUSHROOM_GO_UP;
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