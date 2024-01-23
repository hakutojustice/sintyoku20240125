#include "SceneExplanation.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "SceneFedo.h"

SceneFedo Explanationfedo;

static int ExplanationHandle;  //�摜�n���h���i�[�p�ϐ�

//������
void Explanation_Initialize()
{
	ExplanationHandle = LoadGraph("date/�������.png"); //�摜���[�h
}

//�I������
void Explanation_Finalize()
{
	DeleteGraph(ExplanationHandle);//�摜�̉��
}

//�X�V
void Explanation_Update()
{
	Explanationfedo.UpdateInSetting();

	//Z�L�[��������Ă�����
	if (CheckHitKey(KEY_INPUT_Z) != 0)
	{
		SceneMgr_ChageScene(eScene_Menu); //�V�[�������j���[��ʂɕύX
	}
}

//�`��
void Explanation_Draw()
{
	DrawGraph(0, 0, ExplanationHandle, TRUE);

	DrawString(180, 420, "Z�L�[�������ƃ��j���[��ʂɖ߂�܂�", GetColor(0, 0, 0));
}
