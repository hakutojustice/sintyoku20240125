#include "Background.h"
#include "DxLib.h"

Background::Background():
	BackGroundGraph(-1)
{
}

Background::~Background()
{

}

void Background::Init()
{
	BackGroundGraph = LoadGraph("date/�w�i.png");
}

void Background::Draw()
{
	DrawGraph(0, 0, BackGroundGraph, true);
}
