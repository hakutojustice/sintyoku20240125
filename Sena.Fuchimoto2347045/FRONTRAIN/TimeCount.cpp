#include "TimeCount.h"
#include "DxLib.h"

TimeCount::TimeCount():
	cnt(0),
	test(0),
	EnemyTime(0),
	timenow(0)
{
	time = GetNowCount();    //Œ»İŠÔ‚ğ“¾‚é
	
}

TimeCount::~TimeCount()
{
}

void TimeCount::InitTime()
{

	EnemyTime = 0;
	time = 0;
	time = GetNowCount(); //Œ»İŠÔ‚ğ“¾‚é
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
		//DrawFormatString(300, 0, GetColor(0, 0, 0), "Œo‰ßŠÔ:%d", (GetNowCount() - time) / 1000);
	}
	DrawFormatString(300, 0, GetColor(0, 0, 0), "Œo‰ßŠÔ:%d", (GetNowCount() - time) / 1000);

}
