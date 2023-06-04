#include "BrickDebris.h"
#include "debug.h"

BrickDebris::BrickDebris(float brick_pos_x, float brick_pos_y, int nx, float height)
{
	vx = DEBRIS_BRICK_SPEED_X * nx;
	vy = -DEBRIS_BRICK_SPEED_Y * height;
	x = brick_pos_x;
	y = brick_pos_y;
}

void BrickDebris::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//CGameObject::Update(dt);
	DebugOut(L"[INFO]inside brick debris update\n");
	vy += DEBRIS_BRICK_GRAVITY * dt;
	x += vx * dt;
	y += vy * dt;
}

void BrickDebris::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	RenderBoundingBox();
}