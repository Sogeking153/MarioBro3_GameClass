#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_O:
		mario->SetPosition(4281, 110);
		break;
	case DIK_Z:
		mario->is_holding = true;
		break;
	case DIK_T:
		if (abs(mario->vx) == MARIO_RUNNING_SPEED || mario->GetState() == MARIO_STATE_FLY_HIGH)
			if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
				mario->SetState(MARIO_STATE_FLY_HIGH);
		break;
	case DIK_P:
		//mario->SetState(MARIO_STATE_KICK);
		mario->SetPosition(6818, 210);
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
		if (mario->IsOnTheFlatForm() == false && mario->level == 3)
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
		if (mario->GetLevel() == MARIO_LEVEL_BIG_TAIL)
			mario->SetState(MARIO_STATE_SPIN);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if (mario->GetState() == MARIO_STATE_FLY_LANDING)
			return;
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_Z:
		mario->is_holding = false;
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (mario->GetState() == MARIO_STATE_FLY_HIGH)
		return;

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (mario->level == 3 && mario->state == MARIO_STATE_FLY_LANDING)
		{
			mario->vx = 0.1;
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
		if (mario->level == 3 && mario->state == MARIO_STATE_FLY_LANDING)
		{
			mario->vx = -0.1;
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
		mario->SetState(MARIO_STATE_IDLE);
	}
}