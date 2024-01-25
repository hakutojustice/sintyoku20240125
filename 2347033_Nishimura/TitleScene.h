#pragma once
#include "BaseNumber.h"
class TitleScene
{
public:
	bool Update();
	
	enum TitleMenu
	{
		Player1,
		Player2,
		Option

	};
	


	struct Triangle
	{
		//コマンド三角形を作る座標

		int x2 = 200;//2つの頂点x座標(上)
		int y2 = 290;//2つの頂点y座標(上)
		int x3 = 200;//2つの頂点x座標(下)
		int y3 = y2 + 40;//2つの頂点y座標(下)330
		int x1 = 240;//1つの頂点x座標
		int y1 = (y2 + y3) / 2;//1つの頂点y座標305
	}triangle;


private:
	int gpUpdateKey();
	void MakeSelectTriangle();
};