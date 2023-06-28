#pragma once
#include "GameObject.h"
#include "Effect.h"
#include "MoneyEffect.h"
#include "Mario.h"

#define GAP_HIGHEST_COIN_POS_Y  48*3
#define VY_COIN_EFFECT 0.8f

class CoinEffect :public Effect
{
public:
	bool make_sure_go_down = false;
	bool vanish = false;
	float minPosY;
	float maxPosY;
	MoneyEffect* effect = NULL;

	CoinEffect(float brickX, float brickY);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};