#include "Point.h"
#include "GraphMode.h"
#include "DxLib.h"


Point::Point():
	PointNow(0),
	WenemyPoint(0),
	SenemyPoint(0),
	DenemyPoint(0),
	MovePoint(0),
	PlayerMove(0)
{

}

Point::~Point()
{
}

void Point::InitPoint()
{
	WenemyPoint = 0;
	SenemyPoint = 0;
	DenemyPoint = 0;
	PlayerMove = 1;
	MovePoint = 0;
}

void Point::UpdatePoint(Player& player,int ScrollX)
{
	if (-ScrollX == 1000 * PlayerMove)
	{
		MovePoint += 10;

		PlayerMove++;
	}
}

void Point::DrawPoint(Player& player,int ScrollX)
{

	DrawFormatString(500, 430, GetColor(255, 255, 255), "ˆÚ“®‹——£:%dm", -ScrollX / 100);

	DrawFormatString(300, 460, GetColor(255, 255, 255), "ƒ|ƒCƒ“ƒg:%d", PointNow + WenemyPoint + SenemyPoint + DenemyPoint + MovePoint);
}
