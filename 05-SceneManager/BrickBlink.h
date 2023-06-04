#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
//#include "BrickDebris.h"


#define ID_ANI_BRICKBLINK 746
#define ID_ANI_BRICKBLINK_COIN_STAND_STILL 777


#define BRICKBLINK_WIDTH 48
#define BRICKBLINK_BBOX_WIDTH 48
#define BRICKBLINK_BBOX_HEIGHT 48

#define DEBRIS_DISTANCE 9

#define BRICKBLINK_STATE_IS_HIT 100
#define BRICKBLINK_STATE_COIN 200
#define BRICKBLINK_STATE_BRICK 300

class BrickBlink : public CGameObject {
public:
	bool is_block = true;
	vector<LPGAMEOBJECT> vec_debris;


	bool is_hit = false;
	BrickBlink(float x, float y) : CGameObject(x, y) {   }//SetState(BRICK_BLINK_STATE_COIN);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);

	virtual int IsBlocking() { return is_block; }

	//virtual int IsCollidable() { return 1; };
	//virtual int IsBlocking() { return 1; }
	//int IsBlocking() { return 0; }
};