#include "BrickCoin.h"

void BrickCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK_COIN)->Render(x, y);
	RenderBoundingBox();
}

void BrickCoin::Update(DWORD dt)
{

}

void BrickCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_COIN_BBOX_WIDTH / 2;
	t = y - BRICK_COIN_BBOX_WIDTH / 2;
	r = l + BRICK_COIN_BBOX_WIDTH;
	b = t + BRICK_COIN_BBOX_WIDTH;
}