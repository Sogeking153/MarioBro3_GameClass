#include "GameTime.h"

GameTime* GameTime::__instance = NULL;

GameTime* GameTime::GetInstance()
{
	if (__instance == NULL) __instance = new GameTime();
	return __instance;
}

void GameTime::Update(DWORD dt)
{
	/*if (currentTotalTime + dt > ONE_SECOND_UNIT)
	{
		//get the excess of dt
		currentTotalTime = (currentTotalTime + dt) % ONE_SECOND_UNIT;
		gameTime++;
	}
	else
		currentTotalTime += dt;*/
}

GameTime::GameTime()
{
	currentTotalTime = 0;
	gameTime = 0;
}

GameTime::~GameTime()
{
}