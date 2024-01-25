#include "Application.h"
#include <DxLib.h>
#include <cassert>

#define SCREEN_WIDTH     (1600)                          // ��ʂ̉���
#define SCREEN_HEIGHT    (900)                          // ��ʂ̏c��
#define CHIP_SIZE        (32)                           // ��̃`�b�v�̃T�C�Y


int MyLoaGraph(const TCHAR* path)
{
	int handle = LoadGraph(path);
	assert(handle > 0);
	return handle;
}

bool Application::Init()
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, CHIP_SIZE);
	ChangeWindowMode(true);//�E�B���h�E���[�h�ɂ��܂�
	SetWindowText("�����Q�[��");
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void Application::Run()
{
	while (ProcessMessage() != -1)
	{
		ClearDrawScreen();
		ScreenFlip();
	}
	Terminate();
}

void Application::Terminate()
{
	DxLib_End();
}
