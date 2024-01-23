//Pad�̏����@

//�w�b�_�[�t�@�C���ǂݍ���
#include <DxLib.h>
#include "Pad.h"

//���̃t�@�C���������̊֐��ǂ݂���
namespace
{
	// �O�̃t���[���̃p�b�h�����������
	int lastPad = 0;
	// ���̃t���[���̃p�b�h�����������
	int nowPad = 0;
}
//���̃t�@�C���������̓ǂݍ���
namespace Pad
{
	//�X�V����
	void Update()
	{
		// �O�̃t���[���Ɏ擾�����p�b�h������Â����ɂ���
		lastPad = nowPad;

		// ���݂̃p�b�h�̏����擾����
		nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}
	//�����ꂽ�炳��ĂȂ����̏���
	bool IsPress(int key)
	{
		return (nowPad & key);
	}
	//�O�̃t���[���ŉ����ꂽ��������ĂȂ��̂�
	bool IsTrigger(int key)
	{
		bool isNow = (nowPad & key);	// ���̃t���[��
		bool isLast = (lastPad & key);	// �O�̃t���[��

		return (isNow && !isLast);
	}
	
	bool IsRelase(int key)
	{
		bool isNow = (nowPad & key);	// ���̃t���[��
		bool isLast = (lastPad & key);	// �O�̃t���[��

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
