#pragma once
#include "Effect.h"

#define ANI_MONEY_EFFECT 755
#define VY_MONEY_EFFECT 0.15
#define EFFECT_TIME 300

class MoneyEffect : public Effect
{
public:

	MoneyEffect(int pos_x, int pos_y, int moneyAni = 0);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	~MoneyEffect();
};