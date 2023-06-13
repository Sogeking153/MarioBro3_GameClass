#pragma once
#include "TextAndNumber.h"
#include "Game.h"
#include "GameObject.h"

class UI
{
	LPGAMEOBJECT player = NULL;
	float posX = 100, posY = 800;
	TextAndNumber text;

public:
	UI() {};
	~UI() {};

	void Update() {};
	void Render(int remainingTime, int the_number_mario_hit_brick, int point_hub, int id_map, int world);
	void SetPlayer(LPGAMEOBJECT mario) { player = mario; };
};