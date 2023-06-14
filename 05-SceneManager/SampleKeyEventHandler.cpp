#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

#define IN_SKY_POS_X 4281
#define IN_SKY_POS_Y 110

#define ABOVE_PIPE_IN_SKY_X 6818
#define ABOVE_PIPE_IN_SKY_Y 210

#define VY_FLY_LADING 0.1
#define VY_FLY_HIGH 0.3

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	if (mario->GetState() == MARIO_STATE_TRANSFORM)
		return;

	switch (KeyCode)
	{
	case DIK_M:
		mario->SetState(MARIO_STATE_APPEAR_TAIL);

		//DebugOut(L"[INFO]stransform marioooo\n");
		break;
	case DIK_L:
		mario->SetState(MARIO_STATE_TRANSFORM);

		//DebugOut(L"[INFO]stransform marioooo\n");
		break;
	case DIK_O:
		mario->SetPosition(IN_SKY_POS_X, IN_SKY_POS_Y);
		break;
	case DIK_Z:
		break;
	case DIK_T:
		/*if (abs(mario->vx) == MARIO_RUNNING_SPEED || mario->GetState() == MARIO_STATE_FLY_HIGH)
			if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
				mario->SetState(MARIO_STATE_FLY_HIGH);*/
		break;
	case DIK_P:
		//mario->SetState(MARIO_STATE_KICK);
		mario->SetPosition(ABOVE_PIPE_IN_SKY_X, ABOVE_PIPE_IN_SKY_Y);
		break;
	case DIK_DOWN:
		if (mario->go_down == true)
		{
			mario->is_set_position = true;
			mario->time_to_go_down = GetTickCount64();
			//mario->SetPosition(6750, 1659);
		}
		else
			mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		//mario->SetState(MARIO_STATE_JUMP);
		if (mario->level == MARIO_LEVEL_BIG_TAIL && (abs(mario->vx) == MARIO_RUNNING_SPEED || mario->GetState() == MARIO_STATE_FLY_HIGH))
			mario->SetState(MARIO_STATE_FLY_HIGH);
		else if (mario->level == MARIO_LEVEL_BIG_TAIL && mario->IsOnTheFlatForm() == false)
			mario->SetState(MARIO_STATE_FLY_LANDING);
		else
			mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_BIG_TAIL);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		mario->is_holding = true;
		if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			mario->SetState(MARIO_STATE_SPIN);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_UP:
		mario->is_up_press = true;
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() == MARIO_STATE_TRANSFORM)
		return;

	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetState() == MARIO_STATE_FLY_LANDING)
			return;
		if (mario->GetState() != MARIO_STATE_FLY_HIGH)
			mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->is_holding = false;
		break;
	case DIK_UP: // reset
		mario->is_up_press = false;
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (mario->GetState() == MARIO_STATE_TRANSFORM)
		return;

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (mario->level == MARIO_LEVEL_BIG_TAIL && mario->GetState() == MARIO_STATE_FLY_LANDING)
		{
			mario->vx = VY_FLY_LADING;
			mario->nx = 1;
		}
		else if (mario->level == MARIO_LEVEL_BIG_TAIL && mario->GetState() == MARIO_STATE_FLY_HIGH)
		{
			mario->vx = VY_FLY_HIGH;
			mario->nx = 1;
		}
		else
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			else
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (mario->level == MARIO_LEVEL_BIG_TAIL && mario->GetState() == MARIO_STATE_FLY_LANDING)
		{
			mario->vx = -VY_FLY_LADING;
			mario->nx = -1;
		}
		else if (mario->level == MARIO_LEVEL_BIG_TAIL && mario->GetState() == MARIO_STATE_FLY_HIGH)
		{
			mario->vx = -VY_FLY_HIGH;
			mario->nx = -1;
		}
		else
		{
			if (game->IsKeyDown(DIK_A))
				mario->SetState(MARIO_STATE_RUNNING_LEFT);
			else
				mario->SetState(MARIO_STATE_WALKING_LEFT);
		}
	}
	else
	{
		if (mario->GetState() == MARIO_STATE_SPIN)
			return;
		if (mario->GetState() == MARIO_STATE_FLY_LANDING)
			return;
		if (mario->GetState() == MARIO_STATE_FLY_HIGH)
			return;
		if (mario->GetState() == MARIO_STATE_TRANSFORM)
			return;
		if (mario->GetState() == MARIO_STATE_APPEAR_TAIL)
			return;
		mario->SetState(MARIO_STATE_IDLE);
	}
}