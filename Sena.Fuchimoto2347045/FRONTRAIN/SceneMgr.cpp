#include "SceneMgr.h"
#include "DxLib.h"
#include "Game.h"
#include "Menu.h"
#include "Config.h"
#include "GameOver.h"
#include "SceneExplanation.h"



static eScene mScene = eScene_Menu; //現シーンの管理変数
static eScene mNextScene = eScene_None; //次のシーン管理変数

static void SceneMgr_InitializeModule(eScene scene);//指定モジュールを初期化する
static void SceneMgr_FinalizeModule(eScene scene);//指定モジュールの終了処理を行う

//初期化
void SceneMgr_Initialize()
{
	SceneMgr_InitializeModule(mScene);
}

//終了処理
void SceneMgr_Finalize()
{
	SceneMgr_FinalizeModule(mScene);
}

//更新
void SceneMgr_Update()
{
	if (mNextScene != eScene_None)
	{
		SceneMgr_FinalizeModule(mScene);//現在のシーンの終了処理を実行
		mScene = mNextScene;  //次のシーンを現在のシーンセット
		mNextScene = eScene_None;  //次のシーン情報をクリア
		SceneMgr_InitializeModule(mScene);   //現在のシーンを初期化
	}
	switch (mScene) //シーンによって処理を分岐
	{
	case eScene_Menu://現在の画面がメニューなら
		Menu_Update(); //メニュー画面の更新処理をする
		break;
	case eScene_Game: //現在の画面がゲームなら
		Game_Update(); //ゲーム画面の更新処理をする
		break;
	case eScene_Explanation: //現在の画面が説明画面なら
		Explanation_Update();  //説明画面の更新処理をする
		break;
	case eScene_Config: //現在の画面が設定画面なら
		Config_Update(); //設定画面の更新処理をする
		break;
	case eScene_GameOver://現在の画面がゲームオーバー画面なら
		GameOver_Update(); //ゲームオーバー画面の更新処理をする
		break;
	}
}

//描画
void SceneMgr_Draw()
{
	switch (mScene) //シーンによって処理を分岐
	{
	case eScene_Menu: //現在の画面がメニュー画面なら
		Menu_Draw();  //メニュー画面の描画処理をする
		break;
	case eScene_Game: //現在の画面がゲームなら
		Game_Draw(); //ゲーム画面の描画処理をする
		break;
	case eScene_Explanation: //現在の画面が説明画面なら
		Explanation_Draw(); //説明画面の描画処理をする
		break;
	case eScene_Config: //現在の画面が設定画面なら
		Config_Draw(); //設定画面の描画処理をする
		break;
	case eScene_GameOver://現在の画面がゲームオーバー画面なら
		GameOver_Draw(); //ゲームオーバー画面の描画処理をする
		break;
	}
}

//引数nextSceneにシーンを変更する
void SceneMgr_ChageScene(eScene nextScene)
{
	mNextScene = nextScene; //次のシーンをセットする
}

//引数sceneモジュールを初期化する
static void SceneMgr_InitializeModule(eScene scene)
{
	switch (scene) //シーンによって処理を分岐
	{
	case eScene_Menu: //指定画面がメニュー画面なら
		Menu_Initialize();//メニュー画面の初期化処理をする
		break;
	case eScene_Game: //指定画面がゲーム画面なら
		Game_Initialize();//ゲーム画面の初期化処理を行う
		break;
	case eScene_Explanation:  //指定画面が説明画面なら
		Explanation_Initialize();  //説明画面の初期化処理を行う
		break;
	case eScene_Config: //指定画面が設定画面なら
		Config_Initialize();//設定画面の初期化処理を行う
		break;
	case eScene_GameOver://現在の画面がゲームオーバー画面なら
		GameOver_Initialize(); //ゲームオーバー画面の初期化処理をする
		break;
	}
}

//引数Sceneモジュールの終了処理を行う
static void SceneMgr_FinalizeModule(eScene scene)
{
	switch (scene)  //シーンによって処理を分岐
	{
	case eScene_Menu: //指定画面がメニュー画面なら
		Menu_Finalize();//メニュー画面の終了処理をする
		break;
	case eScene_Game: //指定画面がゲーム画面なら
		Game_Finalize();//ゲーム画面の終了処理を行う
		break;
	case eScene_Explanation:  //指定画面が説明画面なら
		Explanation_Finalize();  //説明画面の処理を行う
		break;
	case eScene_Config: //指定画面が設定画面なら
		Config_Finalize();//設定画面の終了処理を行う
		break;
	case eScene_GameOver://現在の画面がゲームオーバー画面なら
		GameOver_Finalize(); //ゲームオーバー画面の終了処理をする
		break;
	}
}
