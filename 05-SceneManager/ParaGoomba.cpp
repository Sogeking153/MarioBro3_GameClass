#include "ParaGoomba.h"
#include "Goomba.h"
#include "Mario.h"
#include "Brick.h"
#include "FlatForm.h"

//extern  CMario* mario;
ParaGoomba::ParaGoomba(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	//SetState(GOOMBA_STATE_WALKING_LEFT);
	vx = -0.02; //initial setting to go left

	player = mario;
}

void ParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

void ParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void ParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;

	//DebugOut(L"[INFO] state of para goomba is: %d\n", state);

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<FlatForm*>(e->obj))
	{
		if (state == PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING)
			return;
		/*if ((GetState() == GOOMBA_STATE_WALKING_LEFT || GetState() == GOOMBA_STATE_WALKING_RIGHT)
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
		}*/

		if (count % 5 == 0 || count % 5 == 1 || count % 5 == 2)
		{
			SetState(PARA_GOOMBA_STATE_JUMP_SHORT_1);
			count++;
		}
		else if (count % 5 == 3)
		{
			SetState(PARA_GOOMBA_STATE_JUMP_HIGH);
			count++;
		}
		else if (count % 5 == 4)
		{
			if (walking_start == 0)
			{
				float x_player, y_player;
				player->GetPosition(x_player, y_player);
				if (this->x > x_player)
					SetState(PARA_GOOMBA_STATE_WALKING_LEFT);
				else
					SetState(PARA_GOOMBA_STATE_WALKING_RIGHT);
			}
			if (GetTickCount64() - walking_start > 2000 && walking_start)
			{
				walking_start = 0;
				count++;
			}
		}
	}
}

void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == PARA_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	float no_thing;
	CCollision::GetInstance()->Process(this, dt, coObjects);

	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	player->GetBoundingBox(ml, mt, mr, mb);
	//if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	//{
	//	/*this->SetState(GOOMBA_STATE_DIE); */
	//}
}


void ParaGoomba::Render()
{
	int aniId = ID_ANI_PARA_GOOMBA_WALKING;
	if (state == PARA_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARA_GOOMBA_DIE;
	}
	else
	{
		if (vy < 0)
		{
			aniId = ID_ANI_PARA_GOOMBA_JUMP_SMALL;
		}
		if (state == PARA_GOOMBA_STATE_JUMP_HIGH)
			aniId = ID_ANI_PARA_GOOMBA_JUMP_BIG;
		if (state == PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING)
			aniId = ID_ANI_PARA_GOOMBA_WITHOUT_SWING;
	}
	//DebugOut(L"[INFO] vy of para %f\n", vy);

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void ParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARA_GOOMBA_STATE_WALKING_LEFT:
		walking_start = GetTickCount64();
		vx = -0.02;
		break;
	case PARA_GOOMBA_STATE_WALKING_RIGHT:
		walking_start = GetTickCount64();
		vx = 0.02;
		break;
	case PARA_GOOMBA_STATE_JUMP_SHORT_1:
		vy = -0.25 * 1.5;
		break;
	case PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING:
		vx = -0.02;
		break;
	case PARA_GOOMBA_STATE_JUMP_SHORT_3:
		break;
	case PARA_GOOMBA_STATE_JUMP_HIGH:
		vy = -0.25 * 3.5;
		break;
	}
}