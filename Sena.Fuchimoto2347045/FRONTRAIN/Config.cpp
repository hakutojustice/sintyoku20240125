#include "Config.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "SceneFedo.h"

SceneFedo settingfedo;

static int mimageHandle;   //�摜�n���h���i�[�p�ϐ�

//������
void Config_Initialize()
{
	mimageHandle = LoadGraph("date/Menu���.png");//�摜�̃��[�h
}

//�I������
void Config_Finalize()
{
	DeleteGraph(mimageHandle);//�摜�̉��
}

//�X�V
void Config_Update()
{
	settingfedo.UpdateInSetting();

	//Z�L�[��������Ă�����
	if (CheckHitKey(KEY_INPUT_Z) != 0)
	{
		SceneMgr_ChageScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
}

//�`��
void Config_Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
	DrawGraph(0, 0, mimageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 125);

	DrawString(200, 240, "�L�^��ʂł��܂��ł��Ă܂��񂷂��܂���", GetColor(255, 255, 255));
	DrawString(200, 240 + 20, "Z�L�[�������ƃ��j���[��ʂɖ߂�܂�", GetColor(255, 255, 255));
}
