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
	//1���ڕ`��
	DrawGraph(X, Y, Graph, false);

	//2���ڕ`��
	DrawGraph(X + 1600, Y, Graph, false);

	//��ԍ��܂ŃX�N���[�������珉���l�ɖ߂�
	if (X == -1600)
		X = 0;
}

void Background::Move()
{
		X -= SCROLL_SPEED;
}
