#include "SceneExplanation.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "SceneFedo.h"

SceneFedo Explanationfedo;

static int ExplanationHandle;  //画像ハンドル格納用変数

//初期化
void Explanation_Initialize()
{
	ExplanationHandle = LoadGraph("date/操作説明.png"); //画像ロード
}

//終了処理
void Explanation_Finalize()
{
	DeleteGraph(ExplanationHandle);//画像の解放
}

//更新
void Explanation_Update()
{
	Explanationfedo.UpdateInSetting();

	//Zキーが押されていたら
	if (CheckHitKey(KEY_INPUT_Z) != 0)
	{
		SceneMgr_ChageScene(eScene_Menu); //シーンをメニュー画面に変更
	}
}

//描画
void Explanation_Draw()
{
	DrawGraph(0, 0, ExplanationHandle, TRUE);

	DrawString(180, 420, "Zキーを押すとメニュー画面に戻ります", GetColor(0, 0, 0));
}
