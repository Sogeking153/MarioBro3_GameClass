#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 48
#define COIN_BBOX_HEIGHT 48

#define SUPERLEAF_STATE_WALKING 100


class SuperLeaf : public CGameObject {
public:
	SuperLeaf(float x, float y) : CGameObject(x, y) { SetState(SUPERLEAF_STATE_WALKING); };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	virtual void SetState(int state);
};

