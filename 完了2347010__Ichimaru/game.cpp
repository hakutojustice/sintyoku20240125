#include "DxLib.h"
#include "Enemy.h"
#include "Haikei.h"
#include "game.h"
#include "key.h"
#include "Player.h"

enum GameScene NowGameScene;

int Handle = LoadGraph("data/Title.png");
int Handle2 = LoadGraph("data/a.png");

//ゲームシーンの名前
char GameSceneName[GameSceneCount][GameSceneNameMax]
{
	
};

//関数
//タイトル初期化
extern VOID TitleInit(VOID)
{
	 

	return;
}

//タイトル管理
extern bool TitleCtrl(VOID)
{
	auto flg = TitleProc();
	TitleDraw();

	return flg;
}

//タイトル処理
extern bool TitleProc(VOID)
{

	//シーン切り替え
	if (KeyClick(KEY_INPUT_SPACE) == TRUE)
	{
		//スペースキーがおされたとき

		//シーン初期化
		PlayInit();

		//シーン切り替え
		NowGameScene = PlayScene;

		//すぐに切り替える
		return true;


	}

	return false;
}

//タイトル描画
extern VOID TitleDraw(VOID)
{
	if(GameDebug == TRUE)
	{
		Handle = LoadGraph("data/Title.png");
		DrawGraph(0,0,Handle,true);

	}

	return;
}


//プレイ初期化
extern VOID PlayInit(VOID)
{
	
	return;
}

//プレイ管理
extern VOID PlayCtrl(VOID)
{
	PlayProc();
	PlayDraw();

	return;
}

//プレイ処理
extern VOID PlayProc(VOID)
{
	

	return;
}

//プレイ描画
extern VOID PlayDraw(VOID)
{
	if (GameDebug == TRUE)
	{
		
	}

	return;
}


