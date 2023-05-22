#include "ParaGoomba.h"
#include "Goomba.h"
#include "Mario.h"
#include "Brick.h"

//extern  CMario* mario;
ParaGoompa::ParaGoompa(float x, float y, CMario* mario) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING_LEFT);

	player = mario;
}

void ParaGoompa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void ParaGoompa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void ParaGoompa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	DebugOut(L"[INFO] state of para goomba is: %d\n", state);

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	
	if (dynamic_cast<CBrick*>(e->obj))
	{
		if ((GetState() == GOOMBA_STATE_WALKING_LEFT || GetState() == GOOMBA_STATE_WALKING_RIGHT)
			&& GetTickCount64() - walking_start >= 2000 && walking_start)
		{
			SetState(GOOMBA_STATE_JUMP_SHORT_1);
			walking_start = 0;	
		}
		else if (GetState() == GOOMBA_STATE_JUMP_SHORT_1)
		{
			vy = -0.25 * 1.5;
			SetState(GOOMBA_STATE_JUMP_SHORT_2);
		}
		else if (GetState() == GOOMBA_STATE_JUMP_SHORT_2)
		{
			vy = -0.25 * 1.5;
			SetState(GOOMBA_STATE_JUMP_SHORT_3);
		}
		else if (GetState() == GOOMBA_STATE_JUMP_SHORT_3)
		{
			vy = -0.25 * 1.5;
			SetState(GOOMBA_STATE_JUMP_HIGH);
		}
		else if (GetState() == GOOMBA_STATE_JUMP_HIGH)
		{
			vy = -0.25 * 2.5;
			float x_player, y_player;
			player->GetPosition(x_player, y_player);
			if (this->x > x_player)
				SetState(GOOMBA_STATE_WALKING_LEFT);
			else
				SetState(GOOMBA_STATE_WALKING_RIGHT);
		}
	}
}

void ParaGoompa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	float no_thing;
	CCollision::GetInstance()->Process(this, dt, coObjects, no_thing);

	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	player->GetBoundingBox(ml, mt, mr, mb);
	if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	{
		/*this->SetState(GOOMBA_STATE_DIE); */
	}
}


void ParaGoompa::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}

	CAnimations::GetInstance()->Get(ID_ANI_PARA_GOOMBA_WALKING)->Render(x, y);
	RenderBoundingBox();
}

void ParaGoompa::SetState(int state)
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
	case GOOMBA_STATE_WALKING_LEFT:
		walking_start = GetTickCount64();
		vx = -0.02;
		break;
	case GOOMBA_STATE_WALKING_RIGHT:
		walking_start = GetTickCount64();
		vx = 0.02;
		break;
	case GOOMBA_STATE_JUMP_SHORT_1:
		break;
	case GOOMBA_STATE_JUMP_SHORT_2:
		break;
	case GOOMBA_STATE_JUMP_SHORT_3:
		break;
	case GOOMBA_STATE_JUMP_HIGH:
		break;
	}
}