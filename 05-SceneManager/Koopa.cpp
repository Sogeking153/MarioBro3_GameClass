#include "Koopa.h"
#include "Mario.h"
#include "Goomba.h"

//extern  CMario* mario;
Koopa::Koopa(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(CONCO_STATE_FLY_LEFT);
	//SetState(CONCO_STATE_WALKING_LEFT);

	player = mario;
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_INDENT_IN || state == GOOMBA_STATE_SHELL_RUNNING || 
		state == CONCO_STATE_WAS_BROUGHT || state == CONCO_STATE_SHELL_MOVING ||
		state == CONCO_STATE_INDENT_OUT)
	{
		left = x - GOOMBA_BBOX_WIDTH_INDENT_IN / 2;
		top = y - GOOMBA_BBOX_HEIGHT_INDENT_IN / 2;
		right = left + GOOMBA_BBOX_WIDTH_INDENT_IN;
		bottom = top + GOOMBA_BBOX_HEIGHT_INDENT_IN;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
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
	//if (dynamic_cast<Koopa*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;

	if (e->ny != 0)
	{
		if (state == CONCO_STATE_FLY_LEFT)
			vy = -KOOPA_FLYING_SPEED_Y;
		else vy = 0;
	}
	else if (e->nx != 0)
	{
		if (!dynamic_cast<Koopa*>(e->obj))
			vx = -vx;
	}

	if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	//else if (dynamic_cast<CGoomba*>(e->obj))
		//OnCollisionWithGoomba(e);
	if (dynamic_cast<FlatForm*>(e->obj))
		OnCollisionWithFlatForm(e);
}

void Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (this->GetState() == GOOMBA_STATE_SHELL_RUNNING)
	{
		/*	if (goomba->GetX() < this->GetX())
			{
				goomba->is_minus_vx = true;
			}*/
	}
	goomba->SetState(GOOMBA_STATE_WAS_SHOOTED);
	DebugOut(L"[INFO] get in?\n");
}

void Koopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	Koopa* koopa = dynamic_cast<Koopa*>(e->obj);

	/*if (koompas->GetState() == GOOMBA_STATE_SHELL_RUNNING)
	{
		if ( this->GetX() < koompas->GetX() )
		{
			is_minus_vx = true;
			DebugOut(L"[INFO] getting shooted?\n");
		}
		this->SetState(CONCO_STATE_WAS_SHOOTED);
	}*/

	if (koopa->state == GOOMBA_STATE_SHELL_RUNNING)
	{

		if (koopa->GetX() > this->GetX())
		{
			//koompas->is_minus_vx = true;//vx=is_minus_vx?-0.1:0.1;
			koopa->is_minus_vx = true;
		}
		SetState(CONCO_STATE_WAS_SHOOTED);
	}
}

void Koopa::OnCollisionWithFlatForm(LPCOLLISIONEVENT e)
{
	FlatForm* flatform = dynamic_cast<FlatForm*>(e->obj);

	if (this->x > flatform->GetX() + flatform->width - flatform->dodoi && state == CONCO_STATE_WALKING_LEFT)
	{
		vx = -abs(vx);
		DebugOut(L"[INFO] does it get in here?\n");
	}
	else if (this->x < flatform->GetX() - flatform->dodoi && state == CONCO_STATE_WALKING_LEFT)
	{
		vx = abs(vx);
		DebugOut(L"[INFO] does it get in here 222?\n");
	}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//DebugOut(L"[INFO] state koopa %d \n",state);
	if (state == CONCO_STATE_WAS_BROUGHT)
	{
		float x, y;
		player->GetPosition(x, y);
		SetPosition(x + 50, y - 40);
		//return;
	}
	if (state != CONCO_STATE_WAS_BROUGHT)
		vy += 0.002 * dt;
	//vx += ax * dt;

	if ((state == CONCO_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	float nothing;
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (state == GOOMBA_STATE_INDENT_IN && GetTickCount64() - time_to_indent_out > 7000)
	{
		SetState(CONCO_STATE_SHELL_MOVING);

	}
	if (state == CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > 10000)
	{
		SetState(CONCO_STATE_INDENT_OUT);

	}
	if (state == CONCO_STATE_INDENT_OUT && GetTickCount64() - time_to_indent_out > 12000)
	{
		SetPosition(this->x, this->y - 32);//so that shell wont fall off when indent out
		SetState(CONCO_STATE_WALKING_LEFT);
	}

	//float ml, mt, mr, mb;
	//float il, it, ir, ib;

	//this->GetBoundingBox(il, it, ir, ib);
	//player->GetBoundingBox(ml, mt, mr, mb);
	//if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	//{
	//	DebugOut(L"[INFO] bump, kill koopa  \n");
	//	//this->SetState(GOOMBA_STATE_DIE);
	//}
	//DebugOut(L"[INFO] vy of koopa: %f\n", vy);
}


void Koopa::Render()
{
	int aniId = CONCO_ANI_GREEN_WALKING_LEFT;
	if (state == CONCO_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	/*else if (state == GOOMBA_STATE_INDENT_IN || state == 400 || state == GOOMBA_STATE_BEING_HOLDED)
	{
		aniId = ID_ANI_KOOPA_INDENT_IN;
	}*/
	else
	{
		if (state == CONCO_STATE_WALKING_LEFT)
		{
			if (vx > 0)
				aniId = CONCO_ANI_GREEN_WALKING_RIGHT;
			else
				aniId = CONCO_ANI_GREEN_WALKING_LEFT;
		}
		else if (state == GOOMBA_STATE_INDENT_IN)
		{
			aniId = CONCO_ANI_GREEN_INDENT;
		}
		else if (state == GOOMBA_STATE_SHELL_RUNNING)
		{
			aniId = CONCO_ANI_GREEN_RUNNING_SHELL;
		}
		else if (state == CONCO_STATE_SHELL_MOVING)
		{
			aniId = CONCO_ANI_GREEN_SHELL_MOVING;
		}
		else if (state == CONCO_STATE_INDENT_OUT)
		{
			aniId = CONCO_ANI_GREEN_INDENT_OUT;
		}
		else if (state == CONCO_STATE_WAS_SHOOTED)
		{
			aniId = 5402; //ani was shoot
		}
		else if (state == CONCO_STATE_FLY_LEFT)
		{
			if (vx > 0)
				aniId = CONCO_ANI_GREEN_FLY_RIGHT;
			else
				aniId = CONCO_ANI_GREEN_FLY_LEFT;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//for (int i = 0; i < 9; i++)
	//	animations->Get(716 + i)->Render(x + i * 50, y);

	RenderBoundingBox();
}

void Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		//vx = 0;
		break;
	case GOOMBA_STATE_INDENT_IN:
		//vx = -KOOPA_WALKING_SPEED;
		vx = 0;
		vy = 0;
		time_to_indent_out = GetTickCount64();
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		//vx = 0.02;
		vx = player->GetX() > x ? -0.4 : 0.4;
		is_blocking = 1;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_INDENT_OUT:
		break;
	case CONCO_STATE_WAS_SHOOTED:
		vy = -0.6;
		vx = is_minus_vx ? -0.1 : 0.1;
		//vx = 0.09;
		is_colliable = 0;
		break;
	case CONCO_STATE_FLY_LEFT:
		vx = -KOOPA_FLYING_SPEED_Y;
		break;
	}
}