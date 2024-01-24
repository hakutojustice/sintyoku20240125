#include "Time.h"
#include "Player.h"
#include "DxLib.h"

Time::Time():
	Count(0),
	Second(0),
	isTimeUp(false)		// 否定のfalseを挿入
{
}

Time::~Time()
{
}

void Time::Init()
{
	Second = 600.0f;		// 本来は60秒*60
							// 現在は仮で10秒*60[
	isTimeUp = false;
}

void Time::Update()
{
	if (Second <= 0)
	{
		isTimeUp = true;
	}

	Second--;
}

void Time::Draw()
{
	DrawFormatString(80, 100, GetColor(255, 255, 255),
		"残り時間:(%.2f)", Second/60);
}
