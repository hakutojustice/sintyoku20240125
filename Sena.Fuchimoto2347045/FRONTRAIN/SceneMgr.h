#pragma once

typedef enum {
	eScene_Menu,   //メニュー画面
	eScene_Game,   //ゲーム画面
	eScene_Explanation,    //説明画面
	eScene_Config, //設定画面
	eScene_GameOver, //ゲームオーバー画面

	eScene_None,   //無し
}eScene;

void SceneMgr_Initialize();//初期化
void SceneMgr_Finalize();//終了処理
void SceneMgr_Update();//更新
void SceneMgr_Draw();//描画

//引数 nextSceneにシーン変更する
void SceneMgr_ChageScene(eScene nextScene);

