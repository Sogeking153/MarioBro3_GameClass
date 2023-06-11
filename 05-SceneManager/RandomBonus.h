#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "TextAndNumber.h"
#include "Mario.h"

#define RANDOMBONUS_BBOX_WIDTH 48
#define RANDOMBONUS_BBOX_HEIGHT 48

#define STATE_RANDOM_BONUS_MUSHROOM		0
#define STATE_RANDOM_BONUS_STAR			1
#define STATE_RANDOM_BONUS_FIRE_FLOWER	2
#define STATE_GOT_BONUS_MUSHROOM		3
#define STATE_GOT_BONUS_STAR			4
#define STATE_GOT_BONUS_FIRE_FLOWER		5

#define ANI_BONUS_MUSHROOM			749
#define ANI_BONUS_STAR				750
#define ANI_BONUS_FIRE_FLOWER		751
#define ANI_GOT_BONUS_MUSHROOM		752
#define ANI_GOT_BONUS_STAR			753
#define ANI_GOT_BONUS_FIRE_FLOWER	754

#define CARD_MUSHROOM			1
#define CARD_FIRE_FLOWER		2
#define CARD_BONUS_STAR			3

class RandomBonus : public CGameObject
{
public:

	TextAndNumber text;

	DWORD time_order_to_render_text = 0;

	bool got_bonus = false;
	CMario* player = NULL;
	DWORD start_ani = 0;
	RandomBonus(float x, float y, CMario* mario);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);
	int IsBlocking() { return 0; }
};

