#include "Koopa.h"
#include "Mario.h"

//extern  CMario* mario;
Koopa::Koopa(float x, float y, CMario* mario) :CGameObject(x, y)
{
	this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);

	player = mario;
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_INDENT_IN || state == GOOMBA_STATE_SHELL_RUNNING || state == GOOMBA_STATE_BEING_HOLDED)
	{
		left = x - GOOMBA_BBOX_WIDTH_INDENT_IN / 2;
		top = y - GOOMBA_BBOX_HEIGHT_INDENT_IN / 2;
		right = left + GOOMBA_BBOX_WIDTH_INDENT_IN;
		bottom = top + GOOMBA_BBOX_HEIGHT_INDENT_IN;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void Koopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Koopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<Koopa*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"[INFO] state koopa %d \n",state);
	if (state == GOOMBA_STATE_BEING_HOLDED)
	{
		float x, y;
		player->GetPosition(x, y);
		SetPosition(x + 50, y - 40);
		//return;
	}
	if (state != GOOMBA_STATE_BEING_HOLDED)
		vy += 0.002 * dt;
	//vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	player->GetBoundingBox(ml, mt, mr, mb);
	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	{
		DebugOut(L"[INFO] bump, kill koopa  \n");
		//this->SetState(GOOMBA_STATE_DIE);
	}
	//DebugOut(L"[INFO] vy of koopa: %f\n", vy);
}


void Koopa::Render()
{
	int aniId = ID_ANI_KOOPA_WALKING_LEFT;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_INDENT_IN || state==400 || state == GOOMBA_STATE_BEING_HOLDED)
	{
		aniId = ID_ANI_KOOPA_INDENT_IN;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		vx = 0;
		break;
	case GOOMBA_STATE_INDENT_IN:
		//vx = -GOOMBA_WALKING_SPEED;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		vx = 0.02;
		break;
	case GOOMBA_STATE_BEING_HOLDED:
		vx = 0;
		vy = 0;
		break;
	}
}