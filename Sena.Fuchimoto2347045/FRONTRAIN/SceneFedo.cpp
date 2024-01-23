#include "SceneFedo.h"

SceneFedo::SceneFedo():
	c(0),
	a(0),
	b(0),
	White(0),
	end(0),
	Out(0),
	Start(false),
	Setting(false),
	Count(0),
	handle(0)
{
}

SceneFedo::~SceneFedo()
{
}

void SceneFedo::Init()
{
	c = 0;
	a = 0;
	b = 255;
	White = GetColor(255, 255, 255);

	end = 0;

	Out = 0;

	Start = false;

	Setting = false;

	Explanation = false;

	Count = 0;

	handle = LoadGraph("date/スタート画面演出.png");
}

void SceneFedo::Update()
{
	//if (c >= 0 && 256)           //cが0～256の時
		//SetDrawBright(c, c, c);         //段々明るく < (c = 0->255)
	//if (c >= 256 && c < 400)     //cが256～400の時
		//SetDrawBright(255, 255, 255);    //通常の明るさ
	//if (c >= 400 && c < 400 + 256)   //cが400～400+256の時
		//SetDrawBright(255 - (c - 400), 255 - (c - 400), 255 - (c - 400));//段々暗く(c=255->0)

	if (c >= 0 && 256)
		SetDrawBright(255 - c, 255 - c, 255 - c);

	if (Out == 1)
	{
		c++;                 //cをカウントアップ
	}

	if (c >= 256)     //暗くなり終わったら終了
	{
		end = 1;
	}
}

void SceneFedo::StartUpdate()
{
	Count++;
	//1フレーム後
	if (Count >= 56)
	{
		b -= 1;
	}
	

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, b);
	DrawGraph(0, 0, handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneFedo::UpdateInSetting()
{
	end = 0;
	c = 255;

	SetDrawBright(255, 255, 255);
}

void SceneFedo::UpdateIn()
{
	a++;

	if (a >= 0 && 256)
		SetDrawBright(a, a, a);
}

void SceneFedo::DeadOut()
{
	end = 0;
	a = 0;

	SetDrawBright(a, a, a);
}

void SceneFedo::Draw()
{
	DrawBox(0, 0, 640, 480, White, TRUE); //画面全体に白い四角形を描画
}
