#include "DxLib.h"
#include "Background.h"

void Background::Inti()
{
	Graph = LoadGraph("date/background.png");
	X = 0;
	Y = 0;
}

void Background::Draw()
{
	//1枚目描画
	DrawGraph(X, Y, Graph, false);

	//2枚目描画
	DrawGraph(X + 1600, Y, Graph, false);

	//一番左までスクロールしたら初期値に戻す
	if (X == -1600)
		X = 0;
}

void Background::Move()
{
		X -= SCROLL_SPEED;
}
