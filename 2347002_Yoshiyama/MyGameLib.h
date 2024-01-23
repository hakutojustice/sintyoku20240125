#pragma once

#include "DxLib.h"
#include <math.h>

/*���o�͌n*/
/// <summary>
/// �y���[�U��`:static�z�y�ˑ�:Dxlib�z
/// Keybord�̂݁B
/// </summary>
class MyKeyInput
{
private:
	/*static�����o�ϐ�*/
	//���ꂼ���Key�̓��̓t���[����
	static int KeyFrame[];//��`�����s�����Ԃ̓O���[�o���Ő����B
public:
	/*static�����o�֐�*/
	/// <summary>
	/// Key�̓��͏�Ԃ̍X�V�B
	/// ���t���[�����ƂɎ��s���邱�ƂōX�V����B
	/// </summary>
	static void Update()
	{
		// ���݂̃L�[�̓��͏��
		char tmpKey[256];
		// �S�ẴL�[�̓��͏�Ԃ��擾
		GetHitKeyStateAll(tmpKey);
		//�S�Ă�Key�̓��͏�Ԃ̊m�F
		for (int i = 0; i < 256; i++)
		{
			//i�Ԃ�Key��������Ă��邩�𔻒�
			if (tmpKey[i] != 0)
			{
				//�����Ă���Key�̃t���[�������Z
				KeyFrame[i]++;
			}
			else
			{
				//������Ă��Ȃ�Key�̃t���[����������
				KeyFrame[i] = 0;
			}
		}
	}
	/// <summary>
	/// Key�������ꂽ�u�Ԃ��擾����B
	/// Update()�𖈃t���[���s���Ă���O��̊֐��B
	/// </summary>
	/// <param name="KeyCode">Dxlib��KeyCode</param>
	static bool isDownKey(int KeyCode)
	{
		if (KeyFrame[KeyCode] == 1)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Key�������ꑱ���Ă��邩���擾����B
	/// Update()�𖈃t���[���s���Ă���O��̊֐��B
	/// </summary>
	/// <param name="KeyCode">Dxlib��KeyCode</param>
	static bool isHoldKey(int KeyCode)
	{
		if (KeyFrame[KeyCode] >= 1)
		{
			return true;
		}
		return false;
	}
	/// <summary>
	/// Key��������Ă���t���[�������擾����
	/// Update()�𖈃t���[���s���Ă���O��̊֐��B
	/// </summary>
	/// <returns>Dxlib��KeyCode</returns>
	static int HoldKeyTime(int KeyCode)
	{
		if (KeyFrame[KeyCode] >= 1)
		{
			return KeyFrame[KeyCode];
		}
		return 0;
	}
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
};
//�ÓI�����o�ϐ��̎��ԍ쐬
int MyKeyInput::KeyFrame[256];
