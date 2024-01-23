#pragma once

typedef enum {
	eScene_Menu,   //���j���[���
	eScene_Game,   //�Q�[�����
	eScene_Explanation,    //�������
	eScene_Config, //�ݒ���
	eScene_GameOver, //�Q�[���I�[�o�[���

	eScene_None,   //����
}eScene;

void SceneMgr_Initialize();//������
void SceneMgr_Finalize();//�I������
void SceneMgr_Update();//�X�V
void SceneMgr_Draw();//�`��

//���� nextScene�ɃV�[���ύX����
void SceneMgr_ChageScene(eScene nextScene);

