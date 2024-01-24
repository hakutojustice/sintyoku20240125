#include "GameOver.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "SceneFedo.h"

SceneFedo Scenefedo;

static int mimageHandle;  //�摜�n���h���i�[�p�ϐ�

//������
void GameOver_Initialize()
{
	mimageHandle = LoadGraph("date/�Q�[���I�[�o�[���.png");  //�摜�̃��[�h
}

//�I������
void GameOver_Finalize()
{
	DeleteGraph(mimageHandle);   //�摜�̉��
}

//�X�V
void GameOver_Update()
{
	Scenefedo.UpdateIn();

	//SPACE�L�[��������Ă�����
	if (CheckHitKey(KEY_INPUT_SPACE) != 0)
	{
		SceneMgr_ChageScene(eScene_Config);//�V�[�������j���[�ɕύX
	}
}

void GameOver_Draw()
{
	DrawGraph(0, 0, mimageHandle, false);
	DrawString(0, 0, "�Q�[���I�[�o�[��ʂł�", GetColor(255, 255, 255));
	DrawString(0, 20, "SPACE�L�[�������ƃ��j���[��ʂɖ߂�܂�", GetColor(255, 255, 255));
}
