#include "Koopa.h"
#include "Mario.h"
#include "Goomba.h"
#include "BrickCoin.h"
#include "BrickBlink.h"
#include "PlayScene.h"

#define KOOMPAS_VY_WAS_SHOOTED 0.6f
#define KOOMPAS_VX_WAS_SHOOTED 0.1f
#define KOOMPAS_VX_SHELL_RUNNING 0.1f //0.7f

#define GAP_ANI_TO_RED 8

#define GAP_AVOID_FALLING_DOWN 32

#define TIME_TO_SHELL_MOVING	7000
#define TIME_TO_INDENT_OUT		10000
#define TIME_TO_WALKING_LEFT	12000

#define KOOMPAS_AY 0.002

//extern  CMario* mario;
Koopa::Koopa(float x, float y, LPGAMEOBJECT mario, int koopa_type, int koopa_state) :CGameObject(x, y)
{
	this->ax = 0;
	//this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	type = koopa_type;

	//SetState(CONCO_STATE_FLY_LEFT);
	SetState(koopa_state);

	player = dynamic_cast<CMario*>(mario);

	virtualbox = new VirtualBox(x - 50, y, mario);
	CGame* game = CGame::GetInstance();
	CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
	scene->objects.push_back(virtualbox);
}

void Koopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_INDENT_IN || state == GOOMBA_STATE_SHELL_RUNNING || 
		state == CONCO_STATE_WAS_BROUGHT || state == CONCO_STATE_SHELL_MOVING ||
		state == CONCO_STATE_INDENT_OUT || state == CONCO_STATE_BEING_HOLDED)
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

	/*if (state == GOOMBA_STATE_SHELL_RUNNING)
	{
		if (dynamic_cast<CGoomba*>(e->obj)) return;
	}*/

	if (e->ny != 0)
	{
		if (state == CONCO_STATE_FLY_LEFT || state == CONCO_STATE_FLY_RIGHT)
			vy = -KOOPA_FLYING_SPEED_Y;
		else vy = 0;
	}
	else if (e->nx != 0)
	{
		if (!dynamic_cast<Koopa*>(e->obj))
			vx = -vx;
		if (vx > 0)
			virtualbox->SetPosition(this->x + 50, y - 2);
		else
			virtualbox->SetPosition(this->x - 50, y - 2);
		//{
		//	if (this->state == CONCO_STATE_WALKING_LEFT)
		//	{
		//		this->SetState(CONCO_STATE_WALKING_RIGHT);
		//		//virtualbox->SetPosition(this->x + 50, y);
		//	}
		//	else if (this->state == CONCO_STATE_WALKING_RIGHT)
		//	{
		//		this->SetState(CONCO_STATE_WALKING_LEFT);
		//		//virtualbox->SetPosition(this->x - 50, y);
		//	}
		//}
	}

	if (dynamic_cast<Koopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<FlatForm*>(e->obj))
		OnCollisionWithFlatForm(e);
	else if (dynamic_cast<BrickCoin*>(e->obj))
		OnCollisionWithBrickCoin(e);
	else if (dynamic_cast<BrickBlink*>(e->obj))
		OnCollisionWithBrickBlink(e);
}

void Koopa::OnCollisionWithBrickBlink(LPCOLLISIONEVENT e)
{
	if (state == GOOMBA_STATE_SHELL_RUNNING)
	{
		BrickBlink* brick_blink = dynamic_cast<BrickBlink*>(e->obj);
		if (e->nx != 0)
		{
			if (brick_blink->GetState() == BRICKBLINK_STATE_BRICK)
				brick_blink->SetState(BRICKBLINK_STATE_IS_HIT);
		}
	}
}

void Koopa::OnCollisionWithBrickCoin(LPCOLLISIONEVENT e)
{
	if (state == GOOMBA_STATE_SHELL_RUNNING)
	{
		BrickCoin* brick = dynamic_cast<BrickCoin*>(e->obj);
		if (e->nx != 0)
		{
			if (brick->is_hit == false)
				brick->SetState(BRICK_COIN_STATE_HIT);
		}
	}
}

void Koopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	//if (state == GOOMBA_STATE_SHELL_RUNNING)
	//{
	//	/*	if (goomba->GetX() < this->GetX())
	//		{
	//			goomba->is_minus_vx = true;
	//		}*/
	//}
	//DebugOut(L"[INFO] get in?\n");
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
	if (type != KOOPA_RED)
		return;

	FlatForm* flatform = dynamic_cast<FlatForm*>(e->obj);

	//if (this->x > flatform->GetX() + flatform->width - flatform->dodoi && state == CONCO_STATE_WALKING_LEFT)
	//{
	//	vx = -abs(vx);
	//	//DebugOut(L"[INFO] does it get in here?\n");
	//}
	//else if (this->x < flatform->GetX() - flatform->dodoi && state == CONCO_STATE_WALKING_LEFT)
	//{
	//	vx = abs(vx);
	//	//DebugOut(L"[INFO] does it get in here 222?\n");
	//}
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	virtualbox->vx = this->vx;
	//virtualbox->Update(dt, coObjects);

	if (abs(virtualbox->y - this->y) > 15)
	{
		if (this->state == CONCO_STATE_WALKING_LEFT)
		{
			this->SetState(CONCO_STATE_WALKING_RIGHT);
			virtualbox->SetPosition(this->x + 50, y);
		}
		else if (this->state == CONCO_STATE_WALKING_RIGHT)
		{
			this->SetState(CONCO_STATE_WALKING_LEFT);
			virtualbox->SetPosition(this->x - 50, y);
		}
	}
	//DebugOut(L"[INFO] state koopa %d \n",state);
	/*if (state == CONCO_STATE_WAS_BROUGHT)
	{
		float x, y;
		player->GetPosition(x, y);
		SetPosition(x + 50, y - 40);
		//return;
	}*/

	if (state != CONCO_STATE_BEING_HOLDED)
		vy += KOOMPAS_AY * dt;
	//vx += ax * dt;

	if ((state == CONCO_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	float nothing;
	CCollision::GetInstance()->Process(this, dt, coObjects);

	if (state == GOOMBA_STATE_INDENT_IN && GetTickCount64() - time_to_indent_out > TIME_TO_SHELL_MOVING)
	{
		SetState(CONCO_STATE_SHELL_MOVING);

	}
	if (state == CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > TIME_TO_INDENT_OUT)
	{
		SetState(CONCO_STATE_INDENT_OUT);

	}
	if (state == CONCO_STATE_INDENT_OUT && GetTickCount64() - time_to_indent_out > TIME_TO_WALKING_LEFT)
	{
		SetPosition(this->x, this->y - GAP_AVOID_FALLING_DOWN);//so that shell wont fall off when indent out
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
	if (player->GetState() == MARIO_STATE_SPIN)
		this->CheckWetherBeingAttacked(player, CONCO_STATE_WAS_SHOOTED);
}


void Koopa::Render()
{
	//virtualbox->Render();
	int aniId = CONCO_ANI_GREEN_WALKING_LEFT;
	if (state == CONCO_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else
	{
		if (state == CONCO_STATE_WALKING_LEFT || state == CONCO_STATE_WALKING_RIGHT)
		{
			if (vx > 0)
				aniId = CONCO_ANI_GREEN_WALKING_RIGHT;
			else
				aniId = CONCO_ANI_GREEN_WALKING_LEFT;
		}
		else if (state == GOOMBA_STATE_INDENT_IN || state == CONCO_STATE_BEING_HOLDED)
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
			aniId = CONCO_ANI_GREEN_WAS_SHOOTED;
		}
		else if (state == CONCO_STATE_FLY_LEFT || state == CONCO_STATE_FLY_RIGHT)
		{
			if (vx > 0)
				aniId = CONCO_ANI_GREEN_FLY_RIGHT;
			else
				aniId = CONCO_ANI_GREEN_FLY_LEFT;
		}
	}
	if (type == KOOPA_RED)
		aniId -= GAP_ANI_TO_RED;

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
	case CONCO_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
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
		vx = player->GetX() > x ? -KOOMPAS_VX_SHELL_RUNNING : KOOMPAS_VX_SHELL_RUNNING;
		is_blocking = 1;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_INDENT_OUT:
		break;
	case CONCO_STATE_WAS_SHOOTED:
		vy = -KOOMPAS_VY_WAS_SHOOTED;
		vx = DirectionWhenBeingAttack == -1 ? -KOOMPAS_VX_WAS_SHOOTED : KOOMPAS_VX_WAS_SHOOTED;
		//vx = 0.09;
		is_colliable = 0;
		break;
	case CONCO_STATE_FLY_LEFT:
		vx = -KOOPA_FLYING_SPEED_Y;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = KOOPA_FLYING_SPEED_Y;
		break;
	case CONCO_STATE_BEING_HOLDED:
		vx = 0;
		vy = 0;
	}
}