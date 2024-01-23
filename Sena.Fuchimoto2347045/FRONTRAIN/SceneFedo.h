#pragma once
#include "DxLib.h"

class SceneFedo
{
public:
	SceneFedo();
	~SceneFedo();

	void Init();
	void Update();
	void StartUpdate();
	void UpdateInSetting();
	void UpdateIn();
	void DeadOut();
	void Draw();

	int c = 0, White, a;

	int end;

	int Out = 0;

	//スタート画面の変数
	bool Start, Setting, Explanation;

	//スタート画面用の演出ハンドル
	int handle;

	//カウント
	int Count;

	//不透明度
	int b;
};

