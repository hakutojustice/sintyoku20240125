#include "DxLib.h"
#include "Enemy.h"
#include "Haikei.h"
#include "game.h"
#include "key.h"
#include "Player.h"

//グローバル変数

//現在のキーを押しているフレーム数
int NowKeyPressFrame[KeyKindMax];

//1つ前のキーを押しているフレーム数
int OldKeyPressFrame[KeyKindMax];

//関数

//キーボード処理の初期化
VOID KeyInit(VOID)
{
	//配列の初期化
	for (int i = 0; i < KeyKindMax; i++)
	{
		NowKeyPressFrame[i] = 0;
		OldKeyPressFrame[i] = 0;
	}
	return;
}

//キーボード情報の更新
VOID KeyUpdate(VOID)
{
	char KeyState[KeyKindMax];

	GetHitKeyStateAll(&KeyState[0]);

	//キー情報を更新
	for (int i = 0; i < KeyKindMax; i++)
	{
		OldKeyPressFrame[i] = NowKeyPressFrame[i];

		if (KeyState[i] != 0)
		{
			NowKeyPressFrame[i]++;
		}
		else if (KeyState[i] == 0)
		{
			NowKeyPressFrame[i] = 0;
		}
	}

	return;
}

//特定のキーを押したか？
BOOL KeyDown(int KEY_INPUT_)
{
	//現在押されているキーのフレーム数が０よりも上なら
	if (NowKeyPressFrame[KEY_INPUT_] > 0)
	{

		return TRUE;
	}

	return FALSE;
}

BOOL KeyClick(int KEY_INPUT_)
{
	//現在押されているキーのフレーム数が０よりも上なら
	if (NowKeyPressFrame[KEY_INPUT_] == 0
		&& OldKeyPressFrame[KEY_INPUT_] > 0)
	{
		return TRUE;
	}

	return FALSE;
}

int KeyPressFrame(int KEY_INPUT_)
{

	return NowKeyPressFrame[KEY_INPUT_];
}