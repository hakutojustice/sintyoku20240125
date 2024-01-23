#include "SceneMgr.h"
#include "DxLib.h"
#include "Game.h"
#include "Menu.h"
#include "Config.h"
#include "GameOver.h"
#include "SceneExplanation.h"



static eScene mScene = eScene_Menu; //���V�[���̊Ǘ��ϐ�
static eScene mNextScene = eScene_None; //���̃V�[���Ǘ��ϐ�

static void SceneMgr_InitializeModule(eScene scene);//�w�胂�W���[��������������
static void SceneMgr_FinalizeModule(eScene scene);//�w�胂�W���[���̏I���������s��

//������
void SceneMgr_Initialize()
{
	SceneMgr_InitializeModule(mScene);
}

//�I������
void SceneMgr_Finalize()
{
	SceneMgr_FinalizeModule(mScene);
}

//�X�V
void SceneMgr_Update()
{
	if (mNextScene != eScene_None)
	{
		SceneMgr_FinalizeModule(mScene);//���݂̃V�[���̏I�����������s
		mScene = mNextScene;  //���̃V�[�������݂̃V�[���Z�b�g
		mNextScene = eScene_None;  //���̃V�[�������N���A
		SceneMgr_InitializeModule(mScene);   //���݂̃V�[����������
	}
	switch (mScene) //�V�[���ɂ���ď����𕪊�
	{
	case eScene_Menu://���݂̉�ʂ����j���[�Ȃ�
		Menu_Update(); //���j���[��ʂ̍X�V����������
		break;
	case eScene_Game: //���݂̉�ʂ��Q�[���Ȃ�
		Game_Update(); //�Q�[����ʂ̍X�V����������
		break;
	case eScene_Explanation: //���݂̉�ʂ�������ʂȂ�
		Explanation_Update();  //������ʂ̍X�V����������
		break;
	case eScene_Config: //���݂̉�ʂ��ݒ��ʂȂ�
		Config_Update(); //�ݒ��ʂ̍X�V����������
		break;
	case eScene_GameOver://���݂̉�ʂ��Q�[���I�[�o�[��ʂȂ�
		GameOver_Update(); //�Q�[���I�[�o�[��ʂ̍X�V����������
		break;
	}
}

//�`��
void SceneMgr_Draw()
{
	switch (mScene) //�V�[���ɂ���ď����𕪊�
	{
	case eScene_Menu: //���݂̉�ʂ����j���[��ʂȂ�
		Menu_Draw();  //���j���[��ʂ̕`�揈��������
		break;
	case eScene_Game: //���݂̉�ʂ��Q�[���Ȃ�
		Game_Draw(); //�Q�[����ʂ̕`�揈��������
		break;
	case eScene_Explanation: //���݂̉�ʂ�������ʂȂ�
		Explanation_Draw(); //������ʂ̕`�揈��������
		break;
	case eScene_Config: //���݂̉�ʂ��ݒ��ʂȂ�
		Config_Draw(); //�ݒ��ʂ̕`�揈��������
		break;
	case eScene_GameOver://���݂̉�ʂ��Q�[���I�[�o�[��ʂȂ�
		GameOver_Draw(); //�Q�[���I�[�o�[��ʂ̕`�揈��������
		break;
	}
}

//����nextScene�ɃV�[����ύX����
void SceneMgr_ChageScene(eScene nextScene)
{
	mNextScene = nextScene; //���̃V�[�����Z�b�g����
}

//����scene���W���[��������������
static void SceneMgr_InitializeModule(eScene scene)
{
	switch (scene) //�V�[���ɂ���ď����𕪊�
	{
	case eScene_Menu: //�w���ʂ����j���[��ʂȂ�
		Menu_Initialize();//���j���[��ʂ̏���������������
		break;
	case eScene_Game: //�w���ʂ��Q�[����ʂȂ�
		Game_Initialize();//�Q�[����ʂ̏������������s��
		break;
	case eScene_Explanation:  //�w���ʂ�������ʂȂ�
		Explanation_Initialize();  //������ʂ̏������������s��
		break;
	case eScene_Config: //�w���ʂ��ݒ��ʂȂ�
		Config_Initialize();//�ݒ��ʂ̏������������s��
		break;
	case eScene_GameOver://���݂̉�ʂ��Q�[���I�[�o�[��ʂȂ�
		GameOver_Initialize(); //�Q�[���I�[�o�[��ʂ̏���������������
		break;
	}
}

//����Scene���W���[���̏I���������s��
static void SceneMgr_FinalizeModule(eScene scene)
{
	switch (scene)  //�V�[���ɂ���ď����𕪊�
	{
	case eScene_Menu: //�w���ʂ����j���[��ʂȂ�
		Menu_Finalize();//���j���[��ʂ̏I������������
		break;
	case eScene_Game: //�w���ʂ��Q�[����ʂȂ�
		Game_Finalize();//�Q�[����ʂ̏I���������s��
		break;
	case eScene_Explanation:  //�w���ʂ�������ʂȂ�
		Explanation_Finalize();  //������ʂ̏������s��
		break;
	case eScene_Config: //�w���ʂ��ݒ��ʂȂ�
		Config_Finalize();//�ݒ��ʂ̏I���������s��
		break;
	case eScene_GameOver://���݂̉�ʂ��Q�[���I�[�o�[��ʂȂ�
		GameOver_Finalize(); //�Q�[���I�[�o�[��ʂ̏I������������
		break;
	}
}
