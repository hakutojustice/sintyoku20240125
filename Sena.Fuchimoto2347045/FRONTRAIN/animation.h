//#pragma once
////アニメーション処理のヘッダファイル
//
////ヘッダファイル読み込み
//#include "DxLib.h"
//#include "graphic.h"
//#include "SkyEnemy.h"
//#include "DistanceEnemy.h"
//
////エラー
//#define AnimationLoadErrCap   "が読み込め無かった"
//#define AnimationLoadErrTitle  "アニメーションエラー"
//
////文字列の長さ
//#define AnimationPathStrMax 256
//#define AnimationErrStrMax 512
//
////アニメーションファイルのパス
//#define GraphicPathSkyEnemy  ".\\date\\SkyEnemy.png"
//#define AnimSkyEnemyDivX      15               //SkyEnemyの横分割数
//#define AnimSkyEnemyDivY      20               //SkyEnemyの縦分割数
//
//#define GraphicPathBomb      ".\\date\\爆発Down.png"
//#define AnimBombDivX          30
//#define AnimBombDivY          30
//
////アニメーション無限継続
//#define AnimationInfinity     -99999
//
////アニメーション1回のみ
//#define AnimationOnce         -11111
//
////アニメーション構造体のコア部分
//typedef struct _AnimationCore
//{
//	int NowHandleIndex = -1;  //現在のハンドルの要素数
//
//	int DivX = 0;     //画像の横分割数
//	int DivY = 0;     //画像の縦分割数
//
//	int FrameCnt = 0;      //アニメーションのコマ時間
//	int FrameMax = 0;      //アニメーションのコマ時間MAX
//
//	int FrameByFrameCnt = 0;   //アニメーションのコマ送り時間
//	int FrameByFrameMax = 0;   //アニメーションのコマ送り時間MAX
//
//	BOOL IsAnimStartFlg = FALSE;  //アニメーション開始フラグ
//}AnimationCore;
//
////アニメーション構造体
//typedef struct _Animation
//{
//	Graphic     g;  //画像
//	AnimationCore     a; //アニメーションコア
//	int* Handle;    //ハンドル(メモリを動的確保)
//}Animation;
//
////外部グローバル変数
//extern Animation AnimSkyEnemy;  //Skyenemyのアニメーション
//
////外部プロトタイプ宣言
//extern BOOL Animation_Init(VOID);               //読み込み・ハンドル生成
//extern VOID Animation_End(VOID);                //後始末
//extern VOID AnimationLoadErrMessage(const char* path);   //読み込みエラーメッセージ
//
//extern Animation LoadAnimation(const char* path, int XNum, int YNum);   //アニメーション読み込み
//extern VOID DrawAnimation(Animation* animation);                       //描画
//extern VOID DeleteAnimation(Animation animation);                      //解放
//
//extern VOID AnimationStart(Animation* animation, int MillTime, int MillInterval);  //アニメーション開始
