#pragma once

#define GameSceneCount 3
#define GameSceneNameMax 20
#define GameDebug TRUE
#define GameWidth 1600
#define GameHeight 900



//列挙型
enum GameScene
{
	TitleScene,//タイトルシーン
	PlayScene,//プレイシーン
	
};

extern enum GameScene NowGameScene;//現在のゲームシーン

//外部のプロトタイプ宣言
extern VOID TitleInit(VOID); //初期化
extern bool TitleCtrl(VOID); //管理
extern bool TitleProc(VOID); //処理	
extern VOID TitleDraw(VOID); //描画


extern VOID PlayInit(VOID);//初期化
extern VOID PlayCtrl(VOID);//管理
extern VOID PlayProc(VOID);//処理
extern VOID PlayDraw(VOID);//描画

extern VOID GameoverInit(VOID); //初期化
extern VOID GameoverCtrl(VOID); //管理
extern VOID GameoverProc(VOID); //処理	
extern VOID GameoverDraw(VOID); //描画