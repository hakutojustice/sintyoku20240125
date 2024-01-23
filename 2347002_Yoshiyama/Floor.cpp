//����A��̔z�u�\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "Floor.h"

#include "DxLib.h"
#include "Game.h"
#include "SceneMain.h"

//���̃t�@�C������p�̊֐�
namespace
{
	// �L�����N�^�[�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
}


//�R���X�g���N�^
Floor::Floor() :
	i(),
	m_handle(-1)
{
	m_Pos = { 200,600 };
}
//�f�X�g���N�^
Floor::~Floor()
{
}
//����������
void Floor::Init()
{
	// �����蔻��̍X�V
	m_Rect.SetCenter(m_Pos.x, m_Pos.y, kGraphWidth, kGraphHeight);
}
//�X�V����
void Floor::Update()
{
	// �����蔻��̍X�V
	m_Rect.SetCenter(m_Pos.x + i, m_Pos.y + i, kGraphWidth, kGraphHeight);
}
//�`�揈��
void Floor::Draw()
{
	//���摜�̕`��
	DrawRotaGraph(static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y)
		,1.5f, 1.5f,
		kGraphWidth, kGraphHeight,
		m_handle, true);
	
	//�������ɕ\��������@(����+-�ǂꂭ�炢�̒���(i)+-���W����)
	for (i = 0; i < 1300; i++)
	{
		//for���͉��̕��̒����@����͌Œ�
		//��i��
		for (float a = 0; a < 15; a++)
		{
			DrawPixel (m_Pos.x + i - 200, m_Pos.y  - i * 0.05 + a + 100, 0xffffff);
		}
		//��i��
		for (float b = 0; b < 15; b++)
		{
			DrawPixel(m_Pos.x - i + 980, m_Pos.y - i * 0.05  - b - 20, 0xffffff);
			
		}
		//�O�i��
		for (float c = 0; c < 15; c++)
		{
			DrawPixel(m_Pos.x + i - 40, m_Pos.y - i * 0.05 - c - 150, 0xffffff);
		}
		//�l�i��
		for (float d = 0; d < 15; d++)
		{
			DrawPixel(m_Pos.x - i + 980, m_Pos.y - i * 0.05 - d - 300, 0xffffff);
		}
	m_Rect.Draw(0x0000ff, false);
	}

	//��q�̕\��
	for (i = 0; i < 15; i++)
	{
		//for���͏c�̕��̒����@����𒲐߂��ďc�̒������Č�
		//��i�ڈ�ԍ�
		for (float a = 0; a < 60; a++)
		{
			DrawPixel(m_Pos.x + i + 250, m_Pos.y - 1 - a  + 80, 0xff11ff);
			DrawPixel(m_Pos.x + i + 250, m_Pos.y - 1 - a - 0, 0xff11ff);
		}
		//��i�ڈ�ԉE
		for (float b = 0; b < 100; b++)
		{
			DrawPixel(m_Pos.x + i + 800, m_Pos.y - 1 - b + 60, 0xff11ff);
		}
		//��i�ڈ�ԉE
		for (float c = 0; c < 130; c++)
		{
			DrawPixel(m_Pos.x + i + 330, m_Pos.y - 1 - c - 50, 0xff11ff);
		}
		//��i�ڈ�ԍ�
		for (float d = 0; d < 100; d++)
		{
			DrawPixel(m_Pos.x + i + 150, m_Pos.y - 1 - d - 65, 0xff11ff);
		}
		//�O�i�ڈ�ԍ�
		for (float e = 0; e < 60; e++)
		{
			DrawPixel(m_Pos.x + i + 300, m_Pos.y - 1 - e - 180, 0xff11ff);
			DrawPixel(m_Pos.x + i + 300, m_Pos.y - 1 - e - 280, 0xff11ff);
		}
		//�O�i�ڐ^��
		for (float f = 0; f < 150; f++)
		{
			DrawPixel(m_Pos.x + i + 550, m_Pos.y - 1 - f - 180, 0xff11ff);
		}
		//�O�i�ڈ�ԉE
		for (float g = 0; g < 130; g++)
		{
			DrawPixel(m_Pos.x + i + 800, m_Pos.y - 1 - g - 190, 0xff11ff);
		}
	}

	//�S�[���n�_�̏��̕\��
	for (i = 0; i < 15; i++)
	{
		//�Ƃ��ꂽ�P�|�W�V����  ������
		for (float a = 0; a < 120; a++)
		{
			DrawPixel(m_Pos.x + a + 200, m_Pos.y - 1 + i - 460, 0xffffff);
		}
		//�S�[���n�_�@������
		for (float b = 0; b < 120; b++)
		{
			DrawPixel(m_Pos.x + b + 320, m_Pos.y - 1 + i - 470, 0xffffff);
		}
		//�S�[����O�̂͂����@�c����
		for (float c = 0; c < 120; c++)
		{
			DrawPixel(m_Pos.x + i + 360, m_Pos.y - 1 + c - 460, 0xff11ff);
		}
		////�Ƃ��ꂽ�P�|�W�V�����͂��������@�c����
		//for (float d = 0; d < 190; d++)
		//{
		//	DrawPixel(m_Pos.x + i + 130, m_Pos.y - 1 + d - 400, 0xffffff);
		//	DrawPixel(m_Pos.x + i + 100, m_Pos.y - 1 + d - 400, 0xffffff);
		//}
	}


}

bool Floor::IsCol(Rect rect)
{
	return false;
}
