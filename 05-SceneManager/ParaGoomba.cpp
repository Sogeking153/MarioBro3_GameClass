#include "ParaGoomba.h"
#include "Goomba.h"
#include "Mario.h"
#include "Brick.h"
#include "FlatForm.h"
#include "Koopa.h"

//extern  CMario* mario;
ParaGoomba::ParaGoomba(float x, float y, LPGAMEOBJECT mario) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	//SetState(GOOMBA_STATE_WALKING_LEFT);
	vx = -PARAGOOMBA_WALKING_SPEED; //initial setting to go left

	player = dynamic_cast<CMario*>(mario);
}

void ParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == PARA_GOOMBA_STATE_WAS_SHOOTED)
		return;

	if (state == PARA_GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (state == PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT - 2;
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

		if (count % 5 == JUMP_SHORT_0 || count % 5 == JUMP_SHORT_1 || count % 5 == JUMP_SHORT_2)
		{
			SetState(PARA_GOOMBA_STATE_JUMP_SHORT_1);
			count++;
		}
		else if (count % 5 == JUMP_HIGHT)
		{
			SetState(PARA_GOOMBA_STATE_JUMP_HIGH);
			count++;
		}
		else if (count % 5 == WALKING)
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
			if (GetTickCount64() - walking_start > TIME_WALKING && walking_start)
			{
				walking_start = 0;
				count++;
			}
		}
	}
	else if (dynamic_cast<Koopa*>(e->obj))
	{

		Koopa* koopas = dynamic_cast<Koopa*>(e->obj);

		if (koopas->GetState() == GOOMBA_STATE_SHELL_RUNNING)
		{

			if (koopas->GetX() < this->GetX())
			{
				is_minus_vx = true;
			}
			this->SetState(PARA_GOOMBA_STATE_WAS_SHOOTED);
			//DebugOut(L"[INFO] bi ban rui huhu %d\n", state);
		}
	}
	else if (dynamic_cast<CGoomba*>(e->obj))
	{
		/*if (e->ny < 0)
		{
			dynamic_cast<CGoomba*>(e->obj)->SetState(GOOMBA_ADJUST_HEIGHT);
		}*/
	}
}

void ParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (player->x + CAM_DISTANCE > this->x && this->is_cam_coming == false)
	{
		is_cam_coming = true;
	}

	if (is_cam_coming == true)
	{
		vy += ay * dt;
		vx += ax * dt;
		if ((state == PARA_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);


		if (player->GetState() == MARIO_STATE_SPIN)
			this->CheckWetherBeingAttacked(player, PARA_GOOMBA_STATE_WAS_SHOOTED);

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
		if (state == PARA_GOOMBA_STATE_WAS_SHOOTED)
			aniId = ID_ANI_PARA_GOOMBA_WAS_SHOOTED;
	}
	//DebugOut(L"[INFO] vy of para %f\n", vy);

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	if (effect)
		effect->Render();
}

void ParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_GOOMBA_STATE_DIE:
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case PARA_GOOMBA_STATE_WALKING_LEFT:
		walking_start = GetTickCount64();
		vx = -PARAGOOMBA_WALKING_SPEED;
		break;
	case PARA_GOOMBA_STATE_WALKING_RIGHT:
		walking_start = GetTickCount64();
		vx = PARAGOOMBA_WALKING_SPEED;
		break;
	case PARA_GOOMBA_STATE_JUMP_SHORT_1:
		vy = -PARAGOOMBA_VY_SHORT_JUMP;
		break;
	case PARA_GOOMBA_STATE_WALKING_WITHOUT_SWING:
		if (effect == NULL)
			effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);
		vx = -PARAGOOMBA_WALKING_SPEED;
		break;
	case PARA_GOOMBA_STATE_JUMP_SHORT_3:
		break;
	case PARA_GOOMBA_STATE_JUMP_HIGH:
		vy = -PARAGOOMBA_VY_HIGH_JUMP;
		break;
	case PARA_GOOMBA_STATE_WAS_SHOOTED:
		vy = -PARAGOOMBA_VY_BEING_SHOOT;
		vx = DirectionWhenBeingAttack == -1 ? PARAGOOMBA_VX_BEING_SHOOT : -PARAGOOMBA_VX_BEING_SHOOT;
		is_colliable = 0;
		break;
	}
}