//Padの処理　

//ヘッダーファイル読み込み
#include <DxLib.h>
#include "Pad.h"

//このファイル内だけの関数読みこみ
namespace
{
	// 前のフレームのパッド押し下げ状態
	int lastPad = 0;
	// このフレームのパッド押し下げ状態
	int nowPad = 0;
}
//このファイル内だけの読み込み
namespace Pad
{
	//更新処理
	void Update()
	{
		// 前のフレームに取得したパッド情報を一つ古い情報にする
		lastPad = nowPad;

		// 現在のパッドの情報を取得する
		nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}
	//押された顔されてないかの処理
	bool IsPress(int key)
	{
		return (nowPad & key);
	}
	//前のフレームで押されたかおされてないのか
	bool IsTrigger(int key)
	{
		bool isNow = (nowPad & key);	// このフレーム
		bool isLast = (lastPad & key);	// 前のフレーム

		return (isNow && !isLast);
	}
	
	bool IsRelase(int key)
	{
		bool isNow = (nowPad & key);	// このフレーム
		bool isLast = (lastPad & key);	// 前のフレーム

		return (!isNow && isLast);
	}

	bool IsRepeat(int key, int& frame, int RepeatFrame)
	{
		if (IsTrigger(key)) return true;

		if (IsPress(key))
		{
			frame++;

			if (RepeatFrame <= frame)
			{
				frame = 0;

				return true;
			}
		}
		else
		{
			frame = 0;
		}

		return false;
	}
}
