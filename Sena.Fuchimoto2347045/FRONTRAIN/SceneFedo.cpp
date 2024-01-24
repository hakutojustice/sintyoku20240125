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

	handle = LoadGraph("date/�X�^�[�g��ʉ��o.png");
}

void SceneFedo::Update()
{
	//if (c >= 0 && 256)           //c��0�`256�̎�
		//SetDrawBright(c, c, c);         //�i�X���邭 < (c = 0->255)
	//if (c >= 256 && c < 400)     //c��256�`400�̎�
		//SetDrawBright(255, 255, 255);    //�ʏ�̖��邳
	//if (c >= 400 && c < 400 + 256)   //c��400�`400+256�̎�
		//SetDrawBright(255 - (c - 400), 255 - (c - 400), 255 - (c - 400));//�i�X�Â�(c=255->0)

	if (c >= 0 && 256)
		SetDrawBright(255 - c, 255 - c, 255 - c);

	if (Out == 1)
	{
		c++;                 //c���J�E���g�A�b�v
	}

	if (c >= 256)     //�Â��Ȃ�I�������I��
	{
		end = 1;
	}
}

void SceneFedo::StartUpdate()
{
	Count++;
	//1�t���[����
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
	DrawBox(0, 0, 640, 480, White, TRUE); //��ʑS�̂ɔ����l�p�`��`��
}
