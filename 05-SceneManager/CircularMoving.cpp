#include "CircularMoving.h"
void CircularMoving::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(777)->Render(x, y);

	RenderBoundingBox();
}

void CircularMoving::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	count += 0.1 * dt;
	count %= 360;
	x = 2400 + 100 * sin(count * PI / 180);
	y = 900 + 100 * cos(count * PI / 180);
}

void CircularMoving::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - CIRCAL_BBOX_WIDTH / 2;
	t = y - CIRCAL_BBOX_HEIGHT / 2;
	r = l + CIRCAL_BBOX_WIDTH;
	b = t + CIRCAL_BBOX_HEIGHT;
}