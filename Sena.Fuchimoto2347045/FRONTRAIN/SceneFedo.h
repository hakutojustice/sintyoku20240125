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

	//�X�^�[�g��ʂ̕ϐ�
	bool Start, Setting, Explanation;

	//�X�^�[�g��ʗp�̉��o�n���h��
	int handle;

	//�J�E���g
	int Count;

	//�s�����x
	int b;
};

