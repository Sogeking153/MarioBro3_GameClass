#include "Goomba.h"
#include "Mario.h"
#include "Koopa.h"
#include "ParaGoomba.h"

#define GOOMBA_VY_WHEN_WAS_SHOOT 0.6
#define GOOMBA_VX_WHEN_WAS_SHOOT 0.1

CGoomba::CGoomba(float x, float y, LPGAMEOBJECT mario):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	//die_start = -1;
	SetState(GOOMBA_STATE_WALKING);

	player = dynamic_cast<CMario*>(mario);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_WAS_SHOOTED)
		return;
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	//if (dynamic_cast<CGoomba*>(e->obj)) return; 
	if (dynamic_cast<ParaGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;

	if (dynamic_cast<Koopa*>(e->obj))
	{
		Koopa* koopa = dynamic_cast<Koopa*>(e->obj);

		if (koopa->GetState() == GOOMBA_STATE_SHELL_RUNNING)
		{
			if (koopa->GetX() > this->GetX())
			{
				is_minus_vx = true;
			}
			this->SetState(GOOMBA_STATE_WAS_SHOOTED);
		}
	}

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
	{
		// if 2 goomba collide, 1 will change direction at e->nx!=0 and 1 at here
		dynamic_cast<CGoomba*>(e->obj)->vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	if (player->x + CAM_DISTANCE > this->x && this->is_cam_coming == false)
	{
		is_cam_coming = true;
	}

	if (is_cam_coming == true)
	{
		vy += ay * dt;
		vx += ax * dt;

		/*if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}*/
		if (time_to_disapear->IsTimeUp())
		{
			this->Delete();
			return;
		}

		CGameObject::Update(dt, coObjects);
		//float no_thing;
		CCollision::GetInstance()->Process(this, dt, coObjects);

		if (player->GetState() == MARIO_STATE_SPIN)
			this->CheckWetherBeingAttacked(player, GOOMBA_STATE_WAS_SHOOTED);

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


void CGoomba::Render()
{
	if (effect)
		effect->Render();

	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBA_STATE_WAS_SHOOTED)
	{
		aniId = ID_ANI_GOOMBA_WAS_SHOOTED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			time_to_disapear->StartTime();

			if (effect == NULL)
				effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			//vx = 0;
			break;
		case GOOMBA_STATE_WAS_SHOOTED:
			vy = -GOOMBA_VY_WHEN_WAS_SHOOT;
			//DebugOut(L"[INFO] direction shot %d \n", DirectionWhenBeingAttack);
			vx = DirectionWhenBeingAttack == -1 ? -GOOMBA_VX_WHEN_WAS_SHOOT : GOOMBA_VX_WHEN_WAS_SHOOT;
			//vx = 0.09;
			is_colliable = 0;
			break;
		case GOOMBA_ADJUST_HEIGHT:
			y -= GOOMBA_GAP;
			//DebugOut(L"[INFO]adjust height innn %d \n", DirectionWhenBeingAttack);
			break;
	}
}
