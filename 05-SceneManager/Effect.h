#pragma once
#include "GameObject.h"

#define EFFECT_COIN 733

#define EFFECT_TIME 500

class Effect : public CGameObject
{
public:
	ULONGLONG startEffect;
	int effectTime = EFFECT_TIME;

	Effect();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render() = 0;
	~Effect();
};
