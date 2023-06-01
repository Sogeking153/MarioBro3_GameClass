#include "PlantBullet.h"

void PlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
}

void PlantBullet::Render()
{
	int ani = 0;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(704)->Render(x, y);

	RenderBoundingBox();
}

void PlantBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	l = x - PLANT_BULLET_BBOX_WIDTH / 2;
	t = y - PLANT_BULLET_BBOX_HEIGHT / 2;
	r = x + PLANT_BULLET_BBOX_WIDTH / 2;
	b = y + PLANT_BULLET_BBOX_HEIGHT / 2;

}

PlantBullet::PlantBullet(float x, float y)
{
	/*if (direction == 1)
		SetState(PLANT_BULLET_STATE_TOP_RIGHT);
	else if (direction == 2)
		SetState(PLANT_BULLET_STATE_BOT_RIGHT);
	else if (direction == 3)
		SetState(PLANT_BULLET_STATE_BOT_LEFT);
	else if (direction == 4)
		SetState(PLANT_BULLET_STATE_TOP_LEFT);*/
}

void PlantBullet::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case PLANT_BULLET_STATE_TOP_RIGHT:
		vx = PLANT_BULLET_WALKING_SPEED;
		vy = -PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_BOT_RIGHT:
		vx = PLANT_BULLET_WALKING_SPEED;
		vy = PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_BOT_LEFT:
		vx = -PLANT_BULLET_WALKING_SPEED;
		vy = PLANT_BULLET_WALKING_SPEED;
		break;
	case PLANT_BULLET_STATE_TOP_LEFT:
		vx = -PLANT_BULLET_WALKING_SPEED;
		vy = -PLANT_BULLET_WALKING_SPEED;
		break;
	}

}