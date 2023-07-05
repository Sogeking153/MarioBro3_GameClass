#pragma once
#include "Sprites.h"
#include <string>

#define SPACING_LETTER 24
#define START_ANI_NUMBER 200000
#define START_ANI_LETTER 200010
#define ANI_EXCLAIMATION_MARK 200036
#define ANI_SPACE 200037

class TextAndNumber
{
	LPSPRITE textSpr=NULL;
public:
	void Render(float posX, float posY, string str);
	string FillZeroString(string str, int MaxStringLenght);
	TextAndNumber();
	~TextAndNumber();
};

