#include <memory>
#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_  HINSTANCE hPrevInstance, _In_  LPSTR lpCmdLine, int nCmdShow)
{
	/*変数*/
	LONGLONG roopStartTime = 0;
	bool gameRoop = true;

	// 一部の関数はDxLib_Init()の前に実行する必要がある
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	ChangeWindowMode(true);
	//画面サイズの変更

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//ダブルバッファリング
	SetDrawScreen(DX_SCREEN_BACK);

	//Sccene開始
	/*SceneManager* pScene = new SceneManager;
	pScene->Init();*/


	//Sceneの作成//
	auto p_titlleScene = std::make_unique <TitleScene>();
	auto p_gameScene = std::make_unique<GameScene>();


	//DEBUG関数
	SceneKind firstScene = SceneKind::TITLESCENE;
	//Scene変数
	SceneKind nowScene = firstScene;
	SceneKind nextScene = firstScene;
	// ゲームループ
	while (gameRoop)
	{

		// このフレームの開始時刻を覚えておく
		roopStartTime = GetNowHiPerformanceCount();

		// 描画を行う前に画面をクリアする
		ClearDrawScreen();


		// ゲームの処理
		if (nowScene == SceneKind::TITLESCENE)
		{
			//入出力処理
			MyKeyInput::Update();//KeyBord
			
			//計算処理
			nextScene = p_titlleScene->Update();
			//描画処理
			p_titlleScene->Draw();
			//デバッグ処理
		}
		else if (nowScene == SceneKind::GAMESCENE)
		{
			//入出力処理
			MyKeyInput::Update();//KeyBord

			//計算処理
			nextScene = p_gameScene->Update();
			//描画処理
			p_gameScene->Draw();
			//デバッグ処理
		}
		else if (nowScene == SceneKind::GAMEEND)
		{
			gameRoop = false;
		}

		/*Sccene変更初期化処理*/
		if (nextScene != nowScene)
		{
			//シーンの切り替え
			nowScene = nextScene;
			//それぞれのシーンの初期化処理
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

		// 画面が切り替わるのを待つ
		ScreenFlip();

		// escキーでゲーム終了
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60に固定する
		while (GetNowHiPerformanceCount() - roopStartTime < 16667)
		{
			// 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
		}
	}

	//メモリの開放
	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}