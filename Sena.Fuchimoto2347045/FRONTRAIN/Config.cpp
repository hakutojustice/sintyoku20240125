#include "Config.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "SceneFedo.h"

SceneFedo settingfedo;

static int mimageHandle;   //画像ハンドル格納用変数

//初期化
void Config_Initialize()
{
	mimageHandle = LoadGraph("date/Menu画面.png");//画像のロード
}

//終了処理
void Config_Finalize()
{
	DeleteGraph(mimageHandle);//画像の解放
}

//更新
void Config_Update()
{
	settingfedo.UpdateInSetting();

	//Zキーが押されていたら
	if (CheckHitKey(KEY_INPUT_Z) != 0)
	{
		SceneMgr_ChageScene(eScene_Menu);//シーンをメニューに変更
	}
}

//描画
void Config_Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 125);
	DrawGraph(0, 0, mimageHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 125);

	DrawString(200, 240, "記録画面ですまだできてませんすいません", GetColor(255, 255, 255));
	DrawString(200, 240 + 20, "Zキーを押すとメニュー画面に戻ります", GetColor(255, 255, 255));
}
