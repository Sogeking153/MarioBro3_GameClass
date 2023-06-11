#include "Pipe.h"

Pipe::Pipe(float x, float y, int type, int is_pine_can_go)
{
	this->is_pine_can_go = is_pine_can_go;

	if (type == PIPE_TALL)
		SetState(PIPE_STATE_TALL);
	else if (type == PIPE_SHORT)
		SetState(PIPE_STATE_SHORT);
	else if (type == PIPE_BLACK)
		SetState(PIPE_STATE_BLACK);
}

void Pipe::Render()
{
	int ani = 0;
	if (state == PIPE_STATE_TALL)
		ani = ANI_PIPE_TALL;
	else if (state == PIPE_STATE_SHORT)
		ani = ANI_PIPE_SHORT;
	else if (state == PIPE_STATE_BLACK)
		ani = ANI_PIPE_BLACK;

	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani)->Render(x, y);

	RenderBoundingBox();
}

void Pipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == PIPE_STATE_TALL)
	{
		l = x - PIPE_TALL_BBOX_WIDTH / 2;
		t = y - PIPE_TALL_BBOX_HEIGHT / 2;
		r = x + PIPE_TALL_BBOX_WIDTH / 2;
		b = y + PIPE_TALL_BBOX_HEIGHT / 2;
	}
	else if (state == PIPE_STATE_SHORT || state == PIPE_STATE_BLACK)
	{
		l = x - PIPE_SHORT_BBOX_WIDTH / 2;
		t = y - PIPE_SHORT_BBOX_HEIGHT / 2;
		r = x + PIPE_SHORT_BBOX_WIDTH / 2;
		b = y + PIPE_SHORT_BBOX_HEIGHT / 2;
	}
}

void Pipe::SetState(int state)
{
	CGameObject::SetState(state);
}