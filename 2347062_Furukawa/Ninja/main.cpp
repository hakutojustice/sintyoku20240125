#include "DxLib.h"
#include "Background.h"
#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "Map.h"
#include "Application.h"
#include <DxLib.h>
#include <memory>

#define SCREEN_WIDTH     (1600)                          // 画面の横幅
#define SCREEN_HEIGHT    (900)                          // 画面の縦幅
#define CHIP_SIZE        (32)                           // 一つのチップのサイズ

int startTime;

void UpdateTimer()
{
	int currentTime = GetNowCount();
	int elapsedTime = (currentTime - startTime) / 1000;//ミリ秒から秒に変換
	DrawFormatString(800, 800, GetColor(255, 25, 25), "%d", elapsedTime);
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	//Application& application = Application::GeetInstance();
	//if (!application.Init()) 
	//{
	//	return -1;//このアプリは不正終了しました。
	//};
	//application.Run();
	Background background;

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, CHIP_SIZE);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//プレイヤーのメモリ確保
	Player player;

	//プレイヤーのメモリ確保
	Enemy enemy;
	//マップのメモリ確保
	Map map;


	SetDrawScreen(DX_SCREEN_BACK);

	startTime = GetNowCount();


	//各初期化を呼ぶ
	background.Inti();


	// ゲームループ
	while (ProcessMessage() != -1)
	{
		// このフレームの開始時刻を覚えておく
		LONGLONG start = GetNowHiPerformanceCount();
		

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();

		//ゲームの処理
		
		map.Update();
		player.Update(enemy);
		enemy.Update();

		background.Draw();
		background.Move();

		map.Draw();
		player.Draw();
		enemy.Draw();
		UpdateTimer();

		// 画面が切り替わるのを待つ
		ScreenFlip();


		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}