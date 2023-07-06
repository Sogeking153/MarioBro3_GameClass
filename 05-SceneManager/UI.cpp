#include "UI.h"
#include "Sprite.h"
#define ANI_UI 70010
#define UI_POS_X 368
#define UI_POS_Y 645

#define REMAIN_TIME_X 405
#define REMAIN_TIME_Y 658

#define POINT_POS_X 190
#define POINT_POS_Y 658

#define NUMBER_ZERO 7

#define NUMBER_BRICK_POS_X 453
#define NUMBER_BRICK_POS_Y 635

#define WORLD_POS_X 140
#define WORLD_POS_Y 635

#define ID_MAP_POS_X 140
#define ID_MAP_POS_Y 658

#define ANI_PMETER_0 12000
#define ANI_PMETER_1 12001
#define ANI_PMETER_2 12002
#define ANI_PMETER_3 12003
#define ANI_PMETER_4 12004
#define ANI_PMETER_5 12005
#define ANI_PMETER_6 12006

#define VX_PMETER_0 0.31
#define VX_PMETER_1 0.38
#define VX_PMETER_2 0.42
#define VX_PMETER_3 0.52
#define VX_PMETER_4 0.58
#define VX_PMETER_5 0.64
#define VX_PMETER_6 0.7

#define PMETER_POS_X 273
#define PMETER_POS_Y 635

void UI::Render(int remainingTime, int the_number_mario_hit_brick, int point_hub, int id_map, int world)
{
	float x = CGame::GetInstance()->GetCamX();
	float y = CGame::GetInstance()->GetCamY();

	CSprites::GetInstance()->Get(ANI_UI)->Draw(x + UI_POS_X, y + UI_POS_Y);

	text.Render(x + REMAIN_TIME_X, y + REMAIN_TIME_Y, to_string(remainingTime));

	text.Render(x + POINT_POS_X, y + POINT_POS_Y, text.FillZeroString(to_string(point_hub), NUMBER_ZERO));
	//Need fix: number coin mario have
	if (the_number_mario_hit_brick < 10)
	{
		text.Render(x + NUMBER_BRICK_POS_X, y + NUMBER_BRICK_POS_Y, to_string(the_number_mario_hit_brick));
	}
	else text.Render(x + NUMBER_BRICK_POS_X - 21, y + NUMBER_BRICK_POS_Y, to_string(the_number_mario_hit_brick));

	text.Render(x + WORLD_POS_X, y + WORLD_POS_Y, to_string(world));
	text.Render(x + ID_MAP_POS_X, y + ID_MAP_POS_Y, to_string(id_map));

	float speed = abs(player->vx);
	int idAni = ANI_PMETER_0;
	if (speed < VX_PMETER_0)
		idAni = ANI_PMETER_0;
	else if (speed < VX_PMETER_1)
		idAni = ANI_PMETER_1;
	else if (speed < VX_PMETER_2)
		idAni = ANI_PMETER_2;
	else if (speed < VX_PMETER_3)
		idAni = ANI_PMETER_3;
	else if (speed < VX_PMETER_4)
		idAni = ANI_PMETER_4;
	else if (speed < VX_PMETER_5)
		idAni = ANI_PMETER_5;
	else if (speed <= VX_PMETER_6)
		idAni = ANI_PMETER_6;

	CAnimations::GetInstance()->Get(idAni)->Render(x + PMETER_POS_X, y + PMETER_POS_Y);
}