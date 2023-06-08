#include "VenusFireTrap.h"
#include "Mario.h"
#include "Goomba.h"

//extern  CMario* mario;
VenusFireTrap::VenusFireTrap(float x, float y, LPGAMEOBJECT mario, int type) :CGameObject(x, y)
{
	this->type = type;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	SetState(VENUS_STATE_GOING_UP);

	player = mario;

	if (type == 1)
		min_y = y - VENUS_BBOX_HEIGHT - 48 / 2;
	else
		min_y = y - VENUS_BBOX_HEIGHT - 10;

	max_y = y;
	l_safe = x - 90;
	t_safe = 0;
	r_safe = x + 90;
	b_safe = y + 90;
}

void VenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type == GREEN)
	{
		left = x - VENUS_BBOX_WIDTH / 2;
		top = y - GREEN_BBOX_HEIGHT / 2;
		right = x + VENUS_BBOX_WIDTH / 2;
		bottom = y + GREEN_BBOX_HEIGHT / 2;
	}

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

	if (y < min_y && state == VENUS_STATE_GOING_UP)
	{
		vy = 0;
	}

	if (y > min_y && state == VENUS_STATE_GOING_DOWN)
	{
		vy = 0;
	}

	if (state == VENUS_STATE_GOING_UP && GetTickCount64() - time_interval > 2000)
	{
		SetState(VENUS_STATE_SEEING);
	}
	else if (state == VENUS_STATE_SEEING && GetTickCount64() - time_interval > 4000)
	{
		PlantBullet* venus_bullet;
		venus_bullet = new PlantBullet(x, y - 35, player);
		venus_bullet->SetPosition(x, y - 35);

		if (player->GetX() < x)
		{
			if (player->GetY() < y)
				venus_bullet->SetState(PLANT_BULLET_STATE_TOP_LEFT);
			else if (player->GetY() >= y)
				venus_bullet->SetState(PLANT_BULLET_STATE_BOT_LEFT);

		}
		else if (player->GetX() >= x)
		{
			if (player->GetY() < y)
				venus_bullet->SetState(PLANT_BULLET_STATE_TOP_RIGHT);
			else if (player->GetY() >= y)
				venus_bullet->SetState(PLANT_BULLET_STATE_BOT_RIGHT);
		}

		listFireball.push_back(venus_bullet);

		SetState(VENUS_STATE_GOING_DOWN);

	}
	else if (state == VENUS_STATE_GOING_DOWN && GetTickCount64() - time_interval > 9000)
	{
		float l, t, r, b;
		player->GetBoundingBox(l, t, r, b);

		if (this->CheckOverLap(l_safe, t_safe, r_safe, b_safe, l, t, r, b) == false)
		{
			SetState(VENUS_STATE_GOING_UP);
		}
	}

	for (LPGAMEOBJECT fireball : listFireball)
		fireball->Update(dt, coObjects);
}


void VenusFireTrap::Render()
{
	int aniId = VENUS_ANI_SCORPION_DOWN_LEFT;
	if (state == GOOMBA_STATE_DIE)
	{
		//aniId = ID_ANI_GOOMBA_DIE;
	}

	if (type == FIRE)
	{
		RenderToType(FIRE, aniId);
	}
	else if (type == GREEN)
	{
		RenderToType(GREEN, aniId);
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();

	for (LPGAMEOBJECT fireball : listFireball)
		fireball->Render();
}

void VenusFireTrap::RenderToType(int type, int& aniId)
{
	if (player->GetX() <= x)
	{
		if (state == VENUS_STATE_SEEING)
		{
			aniId = VENUS_ANI_SHOOTING_DOWN_LEFT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SHOOTING_UP_LEFT;

		}
		else if (state == VENUS_STATE_GOING_UP || state == VENUS_STATE_GOING_DOWN)
		{

			aniId = VENUS_ANI_SCORPION_DOWN_LEFT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SCORPION_UP_LEFT;
		}


	}
	else if (player->GetX() > x)
	{
		if (state == VENUS_STATE_SEEING)
		{
			aniId = VENUS_ANI_SHOOTING_DOWN_RIGHT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SHOOTING_UP_RIGHT;

		}
		else if (state == VENUS_STATE_GOING_UP || state == VENUS_STATE_GOING_DOWN)
		{

			aniId = VENUS_ANI_SCORPION_DOWN_RIGHT;
			if (player->GetY() <= y)
				aniId = VENUS_ANI_SCORPION_UP_RIGHT;
		}
	}

	if (type == GREEN)
		aniId += 100;
}

bool VenusFireTrap::CheckInArea(float l, float t, float r, float b)
{
	return false;
}

void VenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VENUS_STATE_GOING_UP:
		vy = -VENUS_WALKING_SPEED;
		time_interval = GetTickCount64();
		break;
	case VENUS_STATE_SEEING:
		vy = 0;
		break;
	case VENUS_STATE_GOING_DOWN:
		vy = VENUS_WALKING_SPEED;
		break;
	}
}
