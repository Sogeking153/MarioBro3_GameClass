#include "VenusFireTrap.h"
#include "Mario.h"
#include "Goomba.h"

//extern  CMario* mario;
VenusFireTrap::VenusFireTrap(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(VENUS_STATE_GOING_UP);

	player = mario;
}

void VenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - VENUS_BBOX_WIDTH / 2;
	top = y - VENUS_BBOX_HEIGHT / 2;
	right = x + VENUS_BBOX_WIDTH / 2;
	bottom = y + VENUS_BBOX_HEIGHT / 2;
}

//void VenusFireTrap::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!e->obj->IsBlocking()) return;
//	if (dynamic_cast<CGoomba*>(e->obj)) return;
//
//	if (e->ny != 0)
//	{
//		vy = 0;
//	}
//	else if (e->nx != 0)
//	{
//		vx = -vx;
//	}
//}

void VenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < origin_y - VENUS_BBOX_HEIGHT - 48 / 2)
	{
		vy = 0;
	}
}


void VenusFireTrap::Render()
{
	int aniId = VENUS_ANI_SCORPION_DOWN_LEFT;
	if (state == GOOMBA_STATE_DIE)
	{
		//aniId = ID_ANI_GOOMBA_DIE;
	}

	if (player->GetX() > x)
		aniId += 100;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void VenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_STATE_GOING_UP:
		vy = -VENUS_WALKING_SPEED;
		break;
	}
}
