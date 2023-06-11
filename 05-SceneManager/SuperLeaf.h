#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "debug.h"

#define ID_ANI_COIN 11000

#define SUPER_LEAF_BBOX_WIDTH 16*3
#define SUPER_LEAF_BBOX_HEIGHT 14*3

#define  SUPER_LEAF_STATE_MOVE_LEFT		100
#define  SUPER_LEAF_STATE_MOVE_RIGHT	200
#define  SUPER_LEAF_STATE_MOVE_UP		300

#define  SUPER_LEAF_DISTANT_MOVE_UP		100
#define  SUPER_LEAF_DISTANT_MOVE_HORIZONTALLY		100

#define  SUPER_LEAF_SPEED_VERTICAL		0.1f
#define  SUPER_LEAF_SPEED_HORIZONTAL		0.15f

#define SUPERLEAF_STATE_WALKING 100
#define ANI_SUPER_LEAF 7003

class SuperLeaf : public CGameObject {
public:
	float original_pos_x = x;
	float original_pos_y = y;
	SuperLeaf(float x, float y) : CGameObject(x, y) { SetState(SUPER_LEAF_STATE_MOVE_UP); };
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	virtual void SetState(int state);

	//~SuperLeaf() { DebugOut(L"Super leaf deleted \n"); };
};

