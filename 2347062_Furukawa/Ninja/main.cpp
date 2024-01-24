#include "DxLib.h"
#include "Background.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "Map.h"
#include "Application.h"
#include <DxLib.h>
#include <memory>

#define SCREEN_WIDTH     (1600)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (900)                          // ��ʂ̏c��
#define CHIP_SIZE        (32)                           // ��̃`�b�v�̃T�C�Y

int startTime;

void UpdateTimer()
{
	int currentTime = GetNowCount();
	int elapsedTime = (currentTime - startTime) / 1000;//�~���b����b�ɕϊ�
	DrawFormatString(800, 800, GetColor(255, 25, 25), "%d", elapsedTime);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//Application& application = Application::GeetInstance();
	//if (!application.Init()) 
	//{
	//	return -1;//���̃A�v���͕s���I�����܂����B
	//};
	//application.Run();
	Background background;

	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, CHIP_SIZE);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//�v���C���[�̃������m��
	Player player;

	//�v���C���[�̃������m��
	Enemy enemy;
	//�}�b�v�̃������m��
	Map map;


	SetDrawScreen(DX_SCREEN_BACK);

	startTime = GetNowCount();


	//�e���������Ă�
	background.Inti();


	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();
		

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		//�Q�[���̏���
		
		map.Update();
		player.Update(enemy);
		enemy.Update();

		background.Draw();
		background.Move();

		map.Draw();
		player.Draw();
		enemy.Draw();
		UpdateTimer();

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();


		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}