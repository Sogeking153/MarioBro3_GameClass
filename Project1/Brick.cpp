#include "Brick.h"
#include "debug.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == BRICK_BLINK_STATE_IS_HIT)
		//animations->Get(ID_ANI_DEBRIS_BRICK)->Render(x, y);
	{
		for (int i = 0; i < vec_debris.size(); i++)
		{
			vec_debris[i]->Render();
		}
		return;
	}

	animations->Get(10001)->Render(x, y);

	DebugOut(L"[INFO] brick state %d\n", state);

	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*for (int i = 0; i < vec_debris.size(); i++)
	{
		vec_debris[i]->Update(dt);
	}*/

	for (LPGAMEOBJECT debris : vec_debris)
	{
		debris->Update(dt, coObjects);
		DebugOut(L"[INFO]updating %d\n", vec_debris.size());

	}
	DebugOut(L"[INFO]Does it goes inside Brick? %d\n", vec_debris.size());
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (is_hit == true)
		return;
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state)
{
	switch (state)
	{
	case BRICK_BLINK_STATE_IS_HIT:
		BrickDebris* debrick_brick = NULL;

		debrick_brick = new BrickDebris(x + DEBRIS_DISTANCE, y - DEBRIS_DISTANCE, 1, 1.5);
		vec_debris.push_back(debrick_brick);

		debrick_brick = new BrickDebris(x + DEBRIS_DISTANCE, y + DEBRIS_DISTANCE, 1, 1);
		vec_debris.push_back(debrick_brick);

		debrick_brick = new BrickDebris(x - DEBRIS_DISTANCE, y + DEBRIS_DISTANCE, -1, 1);
		vec_debris.push_back(debrick_brick);

		debrick_brick = new BrickDebris(x - DEBRIS_DISTANCE, y - DEBRIS_DISTANCE, -1, 1.5);

		vec_debris.push_back(debrick_brick);
		break;
	}
	CGameObject::SetState(state);
}