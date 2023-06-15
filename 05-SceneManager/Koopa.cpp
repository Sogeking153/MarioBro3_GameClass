#include "Koopa.h"
#include "Mario.h"
#include "Goomba.h"
#include "BrickCoin.h"
#include "BrickBlink.h"
#include "PlayScene.h"

//extern  CMario* mario;
Koopa::Koopa(float x, float y, LPGAMEOBJECT mario, int koopa_type, int koopa_state) :CGameObject(x, y)
{
	this->ax = 0;
	die_start = -1;
	type = koopa_type;
	SetState(koopa_state);

	player = dynamic_cast<CMario*>(mario);

	if (type == KOOPA_RED)
		virtualbox = new VirtualBox(x - GAP_VIRTUAL_BOX, y, mario);
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
		if (type == KOOPA_RED)
			if (vx > 0)
				virtualbox->SetPosition(this->x + GAP_VIRTUAL_BOX_TURAROUND_X, y - GAP_VIRTUAL_BOX_TURAROUND_Y);
			else
				virtualbox->SetPosition(this->x - GAP_VIRTUAL_BOX_TURAROUND_X, y - GAP_VIRTUAL_BOX_TURAROUND_Y);
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
}

void Koopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (player->x + CAM_DISTANCE > this->x && this->is_cam_coming == false)
	{
		is_cam_coming = true;
	}

	if (is_cam_coming == true)
	{
		if (type == KOOPA_RED)
		{
			virtualbox->vx = this->vx;
			virtualbox->Update(dt, coObjects);
			if (abs(virtualbox->y - this->y) > GAP_VIRTUAL_BOX_TO_KOOPA)
			{
				if (this->state == CONCO_STATE_WALKING_LEFT)
				{
					this->SetState(CONCO_STATE_WALKING_RIGHT);
					virtualbox->SetPosition(this->x + GAP_VIRTUAL_BOX_TURAROUND_X, y);
				}
				else if (this->state == CONCO_STATE_WALKING_RIGHT)
				{
					this->SetState(CONCO_STATE_WALKING_LEFT);
					virtualbox->SetPosition(this->x - GAP_VIRTUAL_BOX_TURAROUND_X, y);
				}
			}
		}

		CGameObject::Update(dt, coObjects);
		if (is_picked == false)
		{
			vy += KOOPA_AY * dt;

		}

		CCollision::GetInstance()->Process(this, dt, coObjects);

		if (state == GOOMBA_STATE_INDENT_IN && GetTickCount64() - time_to_indent_out > TIME_TO_SHELL_MOVING)
		{
			SetState(CONCO_STATE_SHELL_MOVING);
		}
		if (state == CONCO_STATE_SHELL_MOVING && GetTickCount64() - time_to_indent_out > TIME_TO_INDENT_OUT)
		{
			SetPosition(this->x, this->y - GAP_AVOID_FALLING_DOWN);
			SetState(CONCO_STATE_INDENT_OUT);
			if (this->is_picked == true)
			{
				player->CollideWithEnemy();
				player->holding_something = NULL;
				player->SetState(MARIO_STATE_IDLE);
				player->is_holding = false;

				this->is_picked = false;
			}
		}

		if (player->GetState() == MARIO_STATE_SPIN)
			this->CheckWetherBeingAttacked(player, CONCO_STATE_WAS_SHOOTED);

		if (effect)
		{
			effect->Update(dt, coObjects);
			if (effect->isDeleted == true)
			{
				delete effect;
				effect = NULL;
			}
		}
		if (this->y > POS_Y_ENEMY_DELETE)
			this->Delete();
	}

}


void Koopa::Render()
{
	if (type == KOOPA_RED)
		virtualbox->Render();
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

	if (effect)
		effect->Render();

	RenderBoundingBox();
}

void Koopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CONCO_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case CONCO_STATE_WALKING_LEFT:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case CONCO_STATE_WALKING_RIGHT:
		vx = KOOPA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_INDENT_IN:
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);
		vx = 0;
		vy = 0;
		time_to_indent_out = GetTickCount64();
		break;
	case GOOMBA_STATE_SHELL_RUNNING:
		vx = player->GetX() > x ? -KOOPA_VX_SHELL_RUNNING : KOOPA_VX_SHELL_RUNNING;
		is_blocking = 1;
		break;
	case CONCO_STATE_WAS_BROUGHT:
		vx = 0;
		vy = 0;
		break;
	case CONCO_STATE_INDENT_OUT:
		break;
	case CONCO_STATE_WAS_SHOOTED:
		vy = -KOOPA_VY_WAS_SHOOTED;
		vx = DirectionWhenBeingAttack == -1 ? -KOOPA_VX_WAS_SHOOTED : KOOPA_VX_WAS_SHOOTED;
		is_colliable = 0;
		break;
	case CONCO_STATE_FLY_LEFT:
		vx = -KOOPA_FLYING_SPEED_X;
		break;
	case CONCO_STATE_FLY_RIGHT:
		vx = KOOPA_FLYING_SPEED_X;
		break;
	case CONCO_STATE_BEING_HOLDED:
		vx = 0;
		vy = 0;
	}
}