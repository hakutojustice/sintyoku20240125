#include <memory>
#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, int nCmdShow)
{
	/*�ϐ�*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	ChangeWindowMode(true);
	//��ʃT�C�Y�̕ύX

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�_�u���o�b�t�@�����O
	SetDrawScreen(DX_SCREEN_BACK);

	//Sccene�J�n
	/*SceneManager* pScene = new SceneManager;
	pScene->Init();*/


	//Scene�̍쐬//
	auto p_titlleScene = std::make_unique <TitleScene>();
	auto p_gameScene = std::make_unique<GameScene>();


	//DEBUG�֐�
	SceneKind firstScene = SceneKind::TITLESCENE;
	//Scene�ϐ�
	SceneKind nowScene = firstScene;
	SceneKind nextScene = firstScene;
	// �Q�[�����[�v
	while (gameRoop)
	{

		// ���̃t���[���̊J�n�������o���Ă���
		roopStartTime = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();


		// �Q�[���̏���
		if (nowScene == SceneKind::TITLESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();//KeyBord
			
			//�v�Z����
			nextScene = p_titlleScene->Update();
			//�`�揈��
			p_titlleScene->Draw();
			//�f�o�b�O����
		}
		else if (nowScene == SceneKind::GAMESCENE)
		{
			//���o�͏���
			MyKeyInput::Update();//KeyBord

			//�v�Z����
			nextScene = p_gameScene->Update();
			//�`�揈��
			p_gameScene->Draw();
			//�f�o�b�O����
		}
		else if (nowScene == SceneKind::GAMEEND)
		{
			gameRoop = false;
		}

		/*Sccene�ύX����������*/
		if (nextScene != nowScene)
		{
			//�V�[���̐؂�ւ�
			nowScene = nextScene;
			//���ꂼ��̃V�[���̏���������
			if (nowScene == SceneKind::TITLESCENE)
			{
				p_titlleScene->Init();
			}
			else if (nowScene == SceneKind::GAMESCENE)
			{
				p_gameScene->Init();
			}
		}

		//pScene->Update();
		//pScene->Draw();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - roopStartTime < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	//�������̊J��
	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}