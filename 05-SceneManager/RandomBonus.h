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

#define COURSE_CLEAR "COURSE CLEAR !"
#define YOU_GOT_A_CARD "YOU GOT A CARD"

#define ANI_RANDOM_BONUS_BOUNDARY 899

#define RANDOM_BONUS_BOUNDARY_POS_X 8088
#define RANDOM_BONUS_BOUNDARY_POS_Y 1029

#define WHICH_CARD 40040

#define TIME_TO_RENDER_COURSE_CLEAR 1000
#define TIME_TO_RENDER_YOU_GOT_A_CARD 1500
#define TIME_TO_RENDER_CARD 2000

#define RANDOM_BONUS_FLY_VY 0.3f
#define TIME_TO_CHANGE_ITEM 2000

#define FIX_COURSE_CLEAR_X 200
#define FIX_COURSE_CLEAR_Y 100

#define FIX_YOU_GOT_A_CARD_X 170
#define FIX_YOU_GOT_A_CARD_Y 155

#define FIX_CARD_X 550
#define FIX_CARD_Y 155

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

