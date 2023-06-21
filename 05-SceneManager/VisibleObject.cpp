#include "VisibleObject.h"
VisibleObject::VisibleObject(float x, float y, float width, float height, int state)
{
	this->x = x;
	this->y = y;

	this->w = width;
	this->h = height;

	this->state = state;

	if (state == STATE_GUARD)
		vx = VX_GUARD;
}

void VisibleObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + w;
	bottom = top + h;
}

void VisibleObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == STATE_GUARD) {
		if (vx < 0 && x < LEFT_GUARD) {
			x = LEFT_GUARD;
			vx = -vx;
			nx *= -1;

		}

		if (vx > 0 && x > RIGHT_GUARD) {
			x = RIGHT_GUARD;
			vx = -vx;
			nx *= -1;

		}
		CGameObject::Update(dt);
		x += vx * dt;

	}
}

void VisibleObject::Render()
{

	int ani = 0;
	if (state == STATE_GHOST_PLATFORM)
		ani = ANI_GHOST_PLATFORM;
	else if (state == STATE_CACTUS)
		ani = ANI_CACTUS;
	else if (state == STATE_HELP_TAG)
		ani = ANI_HELP_TAG;
	else if (state == STATE_GUARD)
		if (nx == 1)
			ani = ANI_GUARD_RIGHT;
		else
			ani = ANI_GUARD_LEFT;
	else if (state == STATE_3_INTRO)
		ani = ANI_3_INTRO;
	else if (state == STATE_ARROW)
		ani = ANI_ARROW;

	CAnimations::GetInstance()->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}