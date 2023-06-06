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
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);

	player = mario;
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
	if (dynamic_cast<CGoomba*>(e->obj)) return; 
	if (dynamic_cast<ParaGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) return;

	if (dynamic_cast<Koopa*>(e->obj))
	{
		Koopa* Koopas = dynamic_cast<Koopa*>(e->obj);

		if (Koopas->GetX() > this->GetX())
		{
			is_minus_vx = true;
		}
		this->SetState(GOOMBA_STATE_WAS_SHOOTED);
	}

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects); // is this needed here?
	float nothing;
	CCollision::GetInstance()->Process(this, dt, coObjects);

	/*float l_a, t_a, r_a, b_a;
	float l_b, t_b, r_b, b_b;
	this->GetBoundingBox(l_a, t_a, r_a, b_a);
	player->GetBoundingBox(l_b, t_b, r_b, b_b);

	if (this->CheckOverLap(l_a, t_a, r_a, b_a, l_b, t_b, r_b, b_b))
	{
		DebugOut(L"[INFO] inside checkoverlap \n");
	}*/

	float ml, mt, mr, mb;
	float il, it, ir, ib;

	this->GetBoundingBox(il, it, ir, ib);
	player->GetBoundingBox(ml, mt, mr, mb);
	//DebugOut(L"[INFO] mario l is %f \n",ml);

	//if (this->CheckOverLap(il, it, ir, ib, ml, mt, mr, mb))
	//{
		//SetState(CONCO_STATE_WAS_SHOOTED);

		/*DebugOut(L"[INFO] inside Checkoverlap \n");
		this->SetState(GOOMBA_STATE_DIE);*/
	//}
}


void CGoomba::Render()
{
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
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = GOOMBA_WALKING_SPEED;
			//vx = 0;
			break;
		case GOOMBA_STATE_WAS_SHOOTED:
			vy = -GOOMBA_VY_WHEN_WAS_SHOOT;
			vx = is_minus_vx ? GOOMBA_VX_WHEN_WAS_SHOOT : -GOOMBA_VX_WHEN_WAS_SHOOT;
			//vx = 0.09;
			is_colliable = 0;
			break;
	}
}
