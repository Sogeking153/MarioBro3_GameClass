#include "BrickDebris.h"

BrickDebris::BrickDebris(float brick_pos_x, float brick_pos_y, int nx, float height)
{
	vx = DEBRIS_BRICK_SPEED_X * nx; // left right debris
	vy = -DEBRIS_BRICK_SPEED_Y * height; // 2 upper debris 
	x = brick_pos_x;
	y = brick_pos_y;
}

void BrickDebris::Update(DWORD dt)
{
}

void BrickDebris::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	RenderBoundingBox();
}
