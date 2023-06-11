#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 746
#define PBUTTON_WIDTH 16
#define PBUTTON_BBOX_WIDTH 16
#define PBUTTON_BBOX_HEIGHT 16

#define PBUTTON_STATE_IS_HIT 100
#define PBUTTON_STATE_TRANFORM_COIN_TO_BRICK 200

#define ID_ANI_PBUTTON 747
#define ID_ANI_PBUTTON_IS_HIT 748

#define WIDTH_WHEN_WAS_HIT 45

#define TIME_TO_TRANSFER 3000

class PButton : public CGameObject {
public:

	bool is_hit = false;
	ULONGLONG stranform_start = 0;

	PButton(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	void Transform(list<LPGAMEOBJECT> list_bricklink);
};

