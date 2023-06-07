#include "PButton.h"
#include "BrickBlink.h"
#include "debug.h"
#include "PlayScene.h"

//extern vector<LPGAMEOBJECT> list_bricklink;

void PButton::Render()
{
	int ani = ID_ANI_PBUTTON_IS_HIT;
	if (is_hit == false)
		ani = ID_ANI_PBUTTON;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani)->Render(x, y);
}

void PButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetState() == PBUTTON_STATE_IS_HIT && GetTickCount64() - stranform_start >= 3000 && stranform_start)
	{
		SetState(PBUTTON_STATE_TRANFORM_COIN_TO_BRICK);
		stranform_start = 0;



	}
	//DebugOut(L"[INFO] vo khum ta \n");
}

void PButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (is_hit == true)
		return;

	l = x - BRICKBLINK_BBOX_WIDTH / 2;
	t = y - BRICKBLINK_BBOX_HEIGHT / 2;
	r = l + BRICKBLINK_BBOX_WIDTH;
	b = t + BRICKBLINK_BBOX_HEIGHT;
}

void PButton::SetState(int state)
{
	CGame* game = CGame::GetInstance();
	CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
	//scene->is_mario_got_card = true;
	vector<LPGAMEOBJECT> list_bricklink = scene->list_bricklink;

	switch (state)
	{
		//MARIO_STATE_FLY
	case PBUTTON_STATE_IS_HIT:
		stranform_start = GetTickCount64();
		for (int i = 0; i < list_bricklink.size(); i++)
		{
			list_bricklink[i]->SetState(BRICKBLINK_STATE_COIN);
		}
		break;
		//MARIO_STATE_FLY
	case PBUTTON_STATE_TRANFORM_COIN_TO_BRICK:
		for (int i = 0; i < list_bricklink.size(); i++)
		{
			list_bricklink[i]->SetState(BRICKBLINK_STATE_BRICK);
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