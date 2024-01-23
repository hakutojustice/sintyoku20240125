#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Game.h"
#include "SceneFedo.h"
#include "SceneExplanation.h"

SceneFedo fedo;


static int mimageHandle;  //�摜�n���h���i�[�p�ϐ�

bool ContinueInit; //�R���e�j���[�����Ƃ��ɏ���������

//������
void Menu_Initialize()
{
	mimageHandle = LoadGraph("date/�X�^�[�g���.png");    //�摜���[�h

	ContinueInit = true;
}

//�I������
void Menu_Finalize()
{
	DeleteGraph(mimageHandle); //�摜�̉��

	fedo.Init();
}

//�X�V
void Menu_Update()
{

	//ContinueInit��true�Ȃ�1����s����
	if (ContinueInit == true)
	{
		//�Q�[���V�[��������������
		Game_Initialize();

		fedo.Init();
	}
	
	ContinueInit = false;


	fedo.Update();

	//�Q�[���V�[��
	if (fedo.end == 1 && fedo.Start == true)
	{
	
		SceneMgr_ChageScene(eScene_Game);//�V�[�����Q�[����ʂɕύX

		ContinueInit = true;

		
	}
	//�������
	if (fedo.end == 1 && fedo.Explanation == true)
	{
		SceneMgr_ChageScene(eScene_Explanation); //�V�[���������ʂɕύX

		ContinueInit = true;
	}
	//�ݒ���
	if (fedo.end == 1 && fedo.Setting == true)
	{
		SceneMgr_ChageScene(eScene_Config);//�V�[����ݒ��ʂɕύX

		ContinueInit = true;

		
	}



	//A�L�[��������Ă�����
	if (CheckHitKey(KEY_INPUT_A) != 0)
	{

		fedo.Out = 1;
		
		fedo.Start = true;

	}
	//B�L�[��������Ă�����
	if (CheckHitKey(KEY_INPUT_B) != 0)
	{
		fedo.Out = 1;

		fedo.Explanation = true;
	}
	//C�L�[��������Ă�����
	if (CheckHitKey(KEY_INPUT_C) != 0)
	{
		fedo.Out = 1;

		fedo.Setting = true;
		
	}
}

//�`��
void Menu_Draw()
{
	fedo.Draw();

	DrawGraph(0, 0, mimageHandle, false);

	fedo.StartUpdate();

	DrawString(0, 0, "���j���[��ʂł�", GetColor(255, 255, 255));
	DrawString(280, 320, "A�L�[START", GetColor(255, 255, 255));
	DrawString(280, 370, "B�L�[�������", GetColor(255, 255, 255));
	DrawString(280, 420, "C�L�[�L�^", GetColor(255, 255, 255));

}
