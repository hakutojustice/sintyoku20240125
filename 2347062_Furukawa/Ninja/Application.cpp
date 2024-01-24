#include "Application.h"
#include <DxLib.h>
#include <cassert>

#define SCREEN_WIDTH     (1600)                          // 画面の横幅
#define SCREEN_HEIGHT    (900)                          // 画面の縦幅
#define CHIP_SIZE        (32)                           // 一つのチップのサイズ


int MyLoaGraph(const TCHAR* path)
{
	int handle = LoadGraph(path);
	assert(handle > 0);
	return handle;
}

bool Application::Init()
{
	// 一部の関数はDxLib_Init()の前に実行する必要がある
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, CHIP_SIZE);
	ChangeWindowMode(true);//ウィンドウモードにします
	SetWindowText("ランゲーム");
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
