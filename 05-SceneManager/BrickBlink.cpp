#include "BrickBlink.h"
#include "debug.h"
#include "BrickDebris.h"

#define HIGH_DEBRIS 1.5
#define LOW_DEBRIS 1

#define RIGHT_DIRECTION 1
#define LEFT_DIRECTION -1

BrickBlink::BrickBlink(float x, float y, CMario* mario) : CGameObject(x, y)
{
	player = mario;
	this->SetState(BRICKBLINK_STATE_BRICK);
}

void BrickBlink::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int ani = ID_ANI_BRICKBLINK;

	if (state == BRICKBLINK_STATE_IS_HIT)
		//animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	{
		for (int i = 0; i < vec_debris.size(); i++)
		{
			vec_debris[i]->Render();
		}
		return;
	}
	if (state == BRICKBLINK_STATE_COIN)
		ani = ID_ANI_BRICKBLINK_COIN_STAND_STILL;

	animations->Get(ani)->Render(x, y);

	//DebugOut(L"[INFO] state of brick %d\n", state);

	RenderBoundingBox();
}

void BrickBlink::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	for (int i = 0; i < vec_debris.size(); i++)
	{
		vec_debris[i]->Update(dt);
	}

	for (int i = 0; i < vec_debris.size(); i++)
	{
		if (vec_debris[i]->IsDeleted())
		{
			delete vec_debris[i];
			vec_debris[i] = nullptr;
			vec_debris.erase(vec_debris.begin() + i);

			//DebugOut(L"[INFO]delete %d\n", vec_debris.size());
		}
	}

	for (LPGAMEOBJECT debris : vec_debris)
	{
		debris->Update(dt, coObjects);
		//DebugOut(L"[INFO]update %d\n", vec_debris.size());
	}

	if (state == BRICKBLINK_STATE_BRICK)
		this->CheckWetherBeingAttacked(player, BRICKBLINK_STATE_IS_HIT);
}

void BrickBlink::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (is_hit == true)
	{
		//l = t = r = b = 0;
		return;
	}

	l = x - BRICKBLINK_BBOX_WIDTH / 2;
	t = y - BRICKBLINK_BBOX_HEIGHT / 2;
	r = l + BRICKBLINK_BBOX_WIDTH;
	b = t + BRICKBLINK_BBOX_HEIGHT;
}

void BrickBlink::SetState(int state)
{
	BrickDebris* debrick_brick = NULL;

	switch (state)
	{
		//MARIO_STATE_FLY
	case BRICKBLINK_STATE_IS_HIT:



		debrick_brick = new BrickDebris(x + DEBRIS_DISTANCE, y - DEBRIS_DISTANCE, RIGHT_DIRECTION, HIGH_DEBRIS); // top right
		vec_debris.push_back(debrick_brick);


		debrick_brick = new BrickDebris(x + DEBRIS_DISTANCE, y + DEBRIS_DISTANCE, RIGHT_DIRECTION, LOW_DEBRIS);// bottom right
		vec_debris.push_back(debrick_brick);


		debrick_brick = new BrickDebris(x - DEBRIS_DISTANCE, y + DEBRIS_DISTANCE, LEFT_DIRECTION, LOW_DEBRIS);// bottom left
		vec_debris.push_back(debrick_brick);

		debrick_brick = new BrickDebris(x - DEBRIS_DISTANCE, y - DEBRIS_DISTANCE, LEFT_DIRECTION, HIGH_DEBRIS); // top left
		vec_debris.push_back(debrick_brick);

		is_hit = true;

		break;

	case BRICKBLINK_STATE_COIN:
		is_block = false;
		break;

	case BRICKBLINK_STATE_BRICK:
		is_block = true;
		break;

	}

	CGameObject::SetState(state);
}