#pragma once
#include "Sprites.h"
#include <string>

class TextAndNumber
{
	LPSPRITE textSpr;
public:
	void Render(float posX, float posY, string str);

	TextAndNumber() {};
	~TextAndNumber() {};
};

