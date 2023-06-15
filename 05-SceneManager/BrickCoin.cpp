#include "BrickCoin.h"
#include "PButton.h"
#include "PlayScene.h"

#define BRICKCOIN_GAP_BOUNCING 20
#define BRICKCOIN_VX 0.2f

void BrickCoin::Render()
{
	int idAni = ID_ANI_BRICK_QUESION;
	if (state == BRICK_COIN_STATE_HIT)
		idAni = ID_ANI_BRICK_QUESION_IS_HIT;
	CAnimations* animations = CAnimations::GetInstance();
	
	if (has_item == BRICKCOIN_CONTAINS_PBUTTON && state != BRICK_COIN_STATE_HIT)
		idAni = ID_ANI_BRICKBLINK;

	animations->Get(idAni)->Render(x, y);
	/*for (int i = 0; i < 8; i++)
		animations->Get(825 + i)->Render(x + i * 50, y);*/
	//RenderBoundingBox();
}

void BrickCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < originalY - BRICKCOIN_GAP_BOUNCING && vy<0)
	{
		vy = -vy;
		//flag = true;
	}

	else if (vy>0 && y >= originalY)
	{
		vy = 0;
		y = originalY;
		is_hit = true;
		//flag = false;
	}

	if (state != BRICK_COIN_STATE_HIT)
		this->CheckWetherBeingAttacked(player, BRICK_COIN_STATE_HIT);
}

void BrickCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_COIN_BBOX_WIDTH / 2;
	t = y - BRICK_COIN_BBOX_WIDTH / 2;
	r = l + BRICK_COIN_BBOX_WIDTH;
	b = t + BRICK_COIN_BBOX_WIDTH;
}

void BrickCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case BRICK_COIN_STATE_HIT:
		vy = -BRICKCOIN_VX;
		if (has_item == BRICKCOIN_CONTAINS_PBUTTON)
		{
			PButton* pbutton = new PButton(x, y - BRICK_COIN_BBOX_WIDTH);

			CGame* game = CGame::GetInstance();
			CPlayScene* scene = (CPlayScene*)game->GetCurrentScene();
			scene->objects.push_back(pbutton);
		}
		break;
	}
}