//タイトルシーンのヘッダファイル
#pragma once
//ヘッダファイルの読み込み
#include "DxLib.h"
#include "GameCommon.h"
#include "MyGameLib.h"

class TitleScene
{
private:
	SceneKind _nextScene, _tempScene; //シーン遷移用
	int ArrowY;
	int CountFrame;//タイマー用
public:
	TitleScene() :
		_nextScene(SceneKind::TITLESCENE),
		_tempScene(SceneKind::TITLESCENE),
		ArrowY(480),

		CountFrame(0)
	{
	};
	SceneKind Update()
	{
		/*矢印操作*/
		//up
		if (MyKeyInput::isDownKey(KEY_INPUT_UP))
		{
			if (ArrowY <= 480)
			{
				ArrowY = 560;//現在地が一番上なら一番下に移動
			}
			else
			{
				ArrowY -= 40;//40up
			}
		}
		//down
		if (MyKeyInput::isDownKey(KEY_INPUT_DOWN))
		{
			if (ArrowY >= 560)
			{
				ArrowY = 480;//現在地が一番下なら一番上に移動
			}
			else
			{
				ArrowY += 40;//40down
			}
		}
		/*決定処理*/
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			if (ArrowY == 480)
			{
				_nextScene = SceneKind::GAMESCENE;
			}
			else if (ArrowY == 560)
			{
				_nextScene = SceneKind::GAMEEND;
			}
		}
		/*タイマー更新*/
		CountFrame++;
		if (CountFrame > 80000) { CountFrame = 0; }//一定以上増えたら初期化(数は適当)

		return _nextScene;
	}
	void Draw()
	{
		//タイトル表示
		SetFontSize(80);//フォントサイズ上昇

		//ボタン表示
		SetFontSize(20);
		DrawString(600, 480, "GameStart", GetColor(255, 255, 255));
		DrawString(600, 520, "RanKing", GetColor(255, 255, 255));
		DrawString(600, 560, "END", GetColor(255, 255, 255));

		//矢印表示
		if ((CountFrame % 60) < 32)
		{
			DrawString(560, ArrowY, "=>", GetColor(255, 255, 255));
		}
	}
	//インスタンスの初期化
	void Init()
	{
		_nextScene = SceneKind::TITLESCENE;
		_tempScene = SceneKind::TITLESCENE;
		ArrowY = 480;
		CountFrame = 0;
	}
};
