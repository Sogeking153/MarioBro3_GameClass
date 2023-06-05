#include "TextAndNumber.h"

void TextAndNumber::Render(float posX, float posY, string str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			textSpr = CSprites::GetInstance()->Get(str[i] - '0' + 200000);
		else if (str[i] >= 'A' && str[i] <= 'Z')
			textSpr = CSprites::GetInstance()->Get(str[i] - 'A' + 200010);
		else if (str[i] == '!')
			textSpr = CSprites::GetInstance()->Get(200036);
		else if (str[i] == ' ')
			textSpr = CSprites::GetInstance()->Get(200037);
		//textSpr = CSprites::GetInstance()->Get(str[i]-'a'+ 200010);
		//float x, y;
		//CGame::GetInstance()->GetCamPos(x, y);

		textSpr->Draw(posX + i * 25,posY);
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