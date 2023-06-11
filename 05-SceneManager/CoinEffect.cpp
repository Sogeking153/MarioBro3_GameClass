#include "CoinEffect.h"
CoinEffect::CoinEffect(float brickX, float brickY)
{
	x = brickX;
	y = brickY;

	minPosY = brickY - GAP_HIGHEST_COIN_POS_Y;
	maxPosY = brickY;


	vy = -VY_COIN_EFFECT;

}

void CoinEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	Effect::Update(dt, coObjects);

	y += vy * dt;

	if (y < minPosY && make_sure_go_down == false)
	{
		vy = -vy;
		make_sure_go_down = true;
	}
	if (y > maxPosY && vanish == false)
	{
		vanish = true;
		effect = new MoneyEffect(this->x, this->y - EFFECT_GAP);
		//DebugOut(L"[ERROR-------------para die?----------------] DINPUT::GetDeviceData failed. Error: %f\n", vx);
	}

	if (effect)
	{
		effect->Update(dt, coObjects);
		if (effect->isDeleted == true)
		{
			delete effect;
			effect = NULL;
		}
	}
}

void CoinEffect::Render()
{
	if (vanish == false)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(EFFECT_COIN)->Render(x, y);
	}

	if (effect)
		effect->Render();
}
void CoinEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}