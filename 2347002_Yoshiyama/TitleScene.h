//�^�C�g���V�[���̃w�b�_�t�@�C��
#pragma once
//�w�b�_�t�@�C���̓ǂݍ���
#include "DxLib.h"
#include "GameCommon.h"
#include "MyGameLib.h"

class TitleScene
{
private:
	SceneKind _nextScene, _tempScene; //�V�[���J�ڗp
	int ArrowY;
	int CountFrame;//�^�C�}�[�p
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
		/*��󑀍�*/
		//up
		if (MyKeyInput::isDownKey(KEY_INPUT_UP))
		{
			if (ArrowY <= 480)
			{
				ArrowY = 560;//���ݒn����ԏ�Ȃ��ԉ��Ɉړ�
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
				ArrowY = 480;//���ݒn����ԉ��Ȃ��ԏ�Ɉړ�
			}
			else
			{
				ArrowY += 40;//40down
			}
		}
		/*���菈��*/
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
		/*�^�C�}�[�X�V*/
		CountFrame++;
		if (CountFrame > 80000) { CountFrame = 0; }//���ȏ㑝�����珉����(���͓K��)

		return _nextScene;
	}
	void Draw()
	{
		//�^�C�g���\��
		SetFontSize(80);//�t�H���g�T�C�Y�㏸

		//�{�^���\��
		SetFontSize(20);
		DrawString(600, 480, "GameStart", GetColor(255, 255, 255));
		DrawString(600, 520, "RanKing", GetColor(255, 255, 255));
		DrawString(600, 560, "END", GetColor(255, 255, 255));

		//���\��
		if ((CountFrame % 60) < 32)
		{
			DrawString(560, ArrowY, "=>", GetColor(255, 255, 255));
		}
	}
	//�C���X�^���X�̏�����
	void Init()
	{
		_nextScene = SceneKind::TITLESCENE;
		_tempScene = SceneKind::TITLESCENE;
		ArrowY = 480;
		CountFrame = 0;
	}
};
