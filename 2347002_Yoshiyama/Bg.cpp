//�}�b�v�`�b�v�̃\�[�X�t�@�C��
//����͍���Ă݂����g�p���Ȃ��������œ���

//�w�b�_�t�@�C���ǂݍ���
#include <DxLib.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Bg.h"

#include "Game.h"
//�t�@�C������p�̊֐��錾
namespace
{
	// �}�b�v�`�b�v�̏��
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// �`�b�v��u����
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

	// �}�b�v�`�b�v�̔z�u���
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{4,0,8,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
}
//�R���X�g���N�^
Bg::Bg() :
	m_handle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			m_chipData[y][x] = kChipData[y][x];
		}
	}
}
//�f�X�g���N�^
Bg::~Bg()
{
}
//����������
void Bg::Init()
{
	// �}�b�v�`�b�v�̐��𐔂���
	int graphW;
	int graphH;
	GetGraphSize(m_handle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

#if false
	// �f�o�b�N�\��
	printfDx("ChipNumX : %d\n", m_graphChipNumX);
	printfDx("ChipNumY : %d\n", m_graphChipNumY);
#endif

	// �}�b�v�`�b�v�z�u�f�[�^�̓ǂݍ���
	std::fstream file;

	file.open("data/map1.bin", std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		// �t�@�C���̒��g����������ɃR�s�[����
		// static_cast<>()		����̓A�h���X�ȊO�̌^
		// reinterpret_cast<>()	����̓A�h���X�p�̌^
		// const_cast<>()		�����const�����Ȃ��ꍇ�ɂ��������(�g�������ƂȂ�����悭�킩���)
		// �������͈Ⴄ���낤�����͂��̉��߂Ŋ撣�ꎩ��
		file.read(reinterpret_cast<char*>(&m_chipData), sizeof(m_chipData));

		file.close();
	}
}
//�X�V����
void Bg::Update()
{
	
}
//�`�揈��
void Bg::Draw() const
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// �}�b�v��񂩂�u���`�b�v������Ă���
			int chipNo = m_chipData[y][x];

			// �}�b�v�`�b�v�̃O���t�B�b�N�؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(kChipWidth * x, kChipHeight * y,
				srcX, srcY,
				kChipWidth, kChipHeight,
				m_handle, true);
		}
	}
}
