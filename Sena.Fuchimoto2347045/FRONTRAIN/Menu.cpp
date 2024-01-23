#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Game.h"
#include "SceneFedo.h"
#include "SceneExplanation.h"

SceneFedo fedo;


static int mimageHandle;  //画像ハンドル格納用変数

bool ContinueInit; //コンテニューしたときに初期化する

//初期化
void Menu_Initialize()
{
	mimageHandle = LoadGraph("date/スタート画面.png");    //画像ロード

	ContinueInit = true;
}

//終了処理
void Menu_Finalize()
{
	DeleteGraph(mimageHandle); //画像の解放

	fedo.Init();
}

//更新
void Menu_Update()
{

	//ContinueInitがtrueなら1回実行する
	if (ContinueInit == true)
	{
		//ゲームシーンを初期化する
		Game_Initialize();

		fedo.Init();
	}
	
	ContinueInit = false;


	fedo.Update();

	//ゲームシーン
	if (fedo.end == 1 && fedo.Start == true)
	{
	
		SceneMgr_ChageScene(eScene_Game);//シーンをゲーム画面に変更

		ContinueInit = true;

		
	}
	//説明画面
	if (fedo.end == 1 && fedo.Explanation == true)
	{
		SceneMgr_ChageScene(eScene_Explanation); //シーンを説明画面に変更

		ContinueInit = true;
	}
	//設定画面
	if (fedo.end == 1 && fedo.Setting == true)
	{
		SceneMgr_ChageScene(eScene_Config);//シーンを設定画面に変更

		ContinueInit = true;

		
	}



	//Aキーが押されていたら
	if (CheckHitKey(KEY_INPUT_A) != 0)
	{

		fedo.Out = 1;
		
		fedo.Start = true;

	}
	//Bキーが押されていたら
	if (CheckHitKey(KEY_INPUT_B) != 0)
	{
		fedo.Out = 1;

		fedo.Explanation = true;
	}
	//Cキーが押されていたら
	if (CheckHitKey(KEY_INPUT_C) != 0)
	{
		fedo.Out = 1;

		fedo.Setting = true;
		
	}
}

//描画
void Menu_Draw()
{
	fedo.Draw();

	DrawGraph(0, 0, mimageHandle, false);

	fedo.StartUpdate();

	DrawString(0, 0, "メニュー画面です", GetColor(255, 255, 255));
	DrawString(280, 320, "AキーSTART", GetColor(255, 255, 255));
	DrawString(280, 370, "Bキー操作説明", GetColor(255, 255, 255));
	DrawString(280, 420, "Cキー記録", GetColor(255, 255, 255));

}
