#pragma once
#include "Character.h"
class Text
{
public:
	Text();
	~Text();
 
	void GameSceneText(Text&text);

	Character t_chara;

//private:
	
	
	int text_X=0;
	int text_Y=0;
	//プレイヤーの座標表示
	int PlayerCoordinateX;
	int PlayerCoordinataY;

	int GameText[256];
	
	

};




