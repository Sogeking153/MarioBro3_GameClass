#include "SuperLeaf.h"

void SuperLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ANI_SUPER_LEAF)->Render(x, y);
	RenderBoundingBox();
}

void SuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == SUPER_LEAF_STATE_MOVE_UP)
	{
		y += vy * dt;
		x += vx * dt;
		if (this->y <= original_pos_y - SUPER_LEAF_DISTANT_MOVE_UP)
			SetState(SUPER_LEAF_STATE_MOVE_RIGHT);
	}
	if (state == SUPER_LEAF_STATE_MOVE_RIGHT)
	{
		y += vy * dt;
		x += vx * dt;
		if (this->x >= original_pos_x + SUPER_LEAF_DISTANT_MOVE_HORIZONTALLY)
			SetState(SUPER_LEAF_STATE_MOVE_LEFT);
	}
	if (state == SUPER_LEAF_STATE_MOVE_LEFT)
	{
		y += vy * dt;
		x += vx * dt;
		if (this->x <= original_pos_x)
			SetState(SUPER_LEAF_STATE_MOVE_RIGHT);
	}

	this->DeleteWhenOutOfCam();
}

void SuperLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SUPER_LEAF_BBOX_WIDTH / 2;
	t = y - SUPER_LEAF_BBOX_HEIGHT / 2;
	r = l + SUPER_LEAF_BBOX_WIDTH;
	b = t + SUPER_LEAF_BBOX_HEIGHT;
}

void SuperLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case SUPER_LEAF_STATE_MOVE_UP:
		vy = -SUPER_LEAF_SPEED_VERTICAL;
		vx = 0;
		break;
	case SUPER_LEAF_STATE_MOVE_RIGHT:
		vx = SUPER_LEAF_SPEED_HORIZONTAL;
		vy = SUPER_LEAF_SPEED_VERTICAL;
		break;
	case SUPER_LEAF_STATE_MOVE_LEFT:
		vx = -SUPER_LEAF_SPEED_HORIZONTAL;
		vy = SUPER_LEAF_SPEED_VERTICAL;
		break;
	}
}
