#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define ID_ANI_PBUTTON 10010
#define ID_ANI_PBUTTON_IS_HIT 10011
#define PBUTTON_STATE_TRANFORM_COIN_TO_BRICK 200

#define PBUTTON_STATE_IS_HIT 100

class PButton : public CGameObject {
public:
	ULONGLONG stranform_start = 0;

	PButton(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetState(int state);

	void Transform(list<LPGAMEOBJECT> list_bricklink);
};

