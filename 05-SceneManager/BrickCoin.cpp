#include "BrickCoin.h"

void BrickCoin::Render()
{
	int idAni = ID_ANI_BRICK_QUESION;
	if (state == BRICK_COIN_STATE_HIT)
		idAni = ID_ANI_BRICK_QUESION_IS_HIT;
	CAnimations* animations = CAnimations::GetInstance();
	//animations->Get(idAni)->Render(x, y);
	for (int i = 0; i < 8; i++)
		animations->Get(725 + i)->Render(x + i * 50, y);
	RenderBoundingBox();
}

void BrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	//if (y < originalY - 20)
	//{
	//	vy = abs(vy);
	//	//return;
	//}else if (y > originalY)
	//	vy = 0;

	if (y < originalY - 20 && flag == false)
	{
		vy = -vy;
		flag = true;
	}

	else if (flag == true && y >= originalY)
	{
		//DebugOut(L"[ERROR----vy of the brick-----] DINPUT::GetDeviceData failed. Error: %f\n",y);

		vy = 0;
		y = originalY;
		is_hit = true;
		flag = false;
	}
}

void BrickCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_COIN_BBOX_WIDTH / 2;
	t = y - BRICK_COIN_BBOX_WIDTH / 2;
	r = l + BRICK_COIN_BBOX_WIDTH;
	b = t + BRICK_COIN_BBOX_WIDTH;
}

void BrickCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case BRICK_COIN_STATE_HIT:
		vy = -0.2;
		//vx = 0;
		break;
	}
}