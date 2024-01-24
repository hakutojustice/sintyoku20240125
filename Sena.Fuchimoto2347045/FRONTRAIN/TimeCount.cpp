#include "TimeCount.h"
#include "DxLib.h"

TimeCount::TimeCount():
	cnt(0),
	test(0),
	EnemyTime(0),
	timenow(0)
{
	time = GetNowCount();    //現在時間を得る
	
}

TimeCount::~TimeCount()
{
}

void TimeCount::InitTime()
{

	EnemyTime = 0;
	time = 0;
	time = GetNowCount(); //現在時間を得る
	timenow = 0;
}

void TimeCount::UpdateTime(Point& point)
{
	EnemyTime = (GetNowCount() - time) / 1000;

	timenow = (GetNowCount() - time) / 1000;

	if (GetNowCount() - time <= 1000)
	{
		flg = true;
	}

	point.PointNow = timenow * 10;
}

void TimeCount::DrawTime()
{
	if (flg)
	{
		//DrawFormatString(300, 0, GetColor(0, 0, 0), "経過時間:%d", (GetNowCount() - time) / 1000);
	}
	DrawFormatString(300, 0, GetColor(0, 0, 0), "経過時間:%d", (GetNowCount() - time) / 1000);

}
