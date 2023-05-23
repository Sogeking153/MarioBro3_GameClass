#include "PButton.h"

extern vector<LPGAMEOBJECT> list_bricklink;

void PButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
}

void PButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void PButton::SetState(int state)
{
	switch (state)
	{
		//MARIO_STATE_FLY
	case PBUTTON_STATE_IS_HIT:


		for (int i = 0; i < list_bricklink.size(); i++)
		{
			list_bricklink[i]->SetState(200);
		}

		break;
	}

	CGameObject::SetState(state);
}

void PButton::Transform(list<LPGAMEOBJECT> list_bricklink)
{
	for (int i = 0; i < list_bricklink.size(); i++)
	{
		//list_bricklink->at
		//list_bricklink[i]->set
			//list_bricklink.at(i)->SetState(100);
	}
}