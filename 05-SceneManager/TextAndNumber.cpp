#include "TextAndNumber.h"
#include "debug.h"

void TextAndNumber::Render(float posX, float posY, string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			textSpr = CSprites::GetInstance()->Get(str[i] - '0' + START_ANI_NUMBER);
		else if (str[i] >= 'A' && str[i] <= 'Z')
			textSpr = CSprites::GetInstance()->Get(str[i] - 'A' + START_ANI_LETTER);
		else if (str[i] == '!')
			textSpr = CSprites::GetInstance()->Get(ANI_EXCLAIMATION_MARK);
		else if (str[i] == ' ')
			textSpr = CSprites::GetInstance()->Get(ANI_SPACE);
		//textSpr = CSprites::GetInstance()->Get(str[i]-'a'+ 200010);
		//float x, y;
		//CGame::GetInstance()->GetCamPos(x, y);

		//DebugOut(L"[INFO]your value sir : %d\n", textSpr);

		textSpr->Draw(posX + i * SPACING_LETTER, posY);
	}

}

string TextAndNumber::FillZeroString(string str, int MaxStringLenght)
{
	while (str.size() < MaxStringLenght)
		str = "0" + str;
	return str;
}

TextAndNumber::TextAndNumber()
{

}

TextAndNumber::~TextAndNumber()
{

}