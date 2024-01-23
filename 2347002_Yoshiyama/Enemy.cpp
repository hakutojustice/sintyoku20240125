//�v���C���[�̃\�[�X�t�@�C��

//�w�b�_�t�@�C���̓ǂݍ���
#include <Dxlib.h>
#include "Game.h"
#include "SceneMain.h"
#include "Pad.h"
#include "Enemy.h"

#define ENEMY_MAX 5

//���̃t�@�C�����ł����g���Ȃ��֐��\�L
namespace
{
	//�ړ����x
	constexpr float kSpeed = 1.0f;

	//character�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	//character�A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,1 };

	//�A�j���[�V����1��̃t���[����
	constexpr int kAnimeFrameNum = 12;

	constexpr int kAnimeFrameCycle = _countof(kUseFrame) * kAnimeFrameNum;

	//�����̃T�C�Y
	constexpr int kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr int kGraphHalfHeight = kGraphHeight / 2.0f;
}
//�R���X�g���N�^
Enemy::Enemy():
	m_handle(-1),
	m_pos(100,250),
	m_dir(kDirDown),
	m_MoveDir(0,3),
	m_Move(0,0),
	m_walkAnimeFrame(kAnimeFrameNum),
	m_isExist(false),
	Time(0),
	i(0)
{
}
//�f�X�g���N�^
Enemy::~Enemy()
{
}
//����������
void Enemy::Init()
{
	//�����蔻��̍X�V
	m_Rect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);

	//Enemy�̍��W�̍X�V
	m_pos.x = 100;
	m_pos.y = 250;

	
}
//�X�V����
void Enemy::Update()
{
	//�����蔻��̍X�V
	m_Rect.SetCenter(m_pos.x + i, m_pos.y + i, kGraphWidth, kGraphHeight);

	bool isMove = false;//�ړ������ǂ���

	/*��������*/
	//����
	m_pos.y++;

	//���̍⓹�ϊ�
	//�����v���O�������͉��̏��Ԃł̎���
	if (m_pos.y > 610)
	{
		//��i��
		for (int x = 0; x <= Game::kScreenWidth; x++)
		{
			//X�̒l�Ɣ�r����
			//static�͕ϐ��ϊ�
			if (static_cast<int>(m_pos.x) == x)
			{
				m_pos.y = 685 - x * 0.05f;
			}
				m_pos.x= m_pos.x - 1 * 0.005f;
				Reverse = false;
		}
	}
	else if (m_pos.y >= 490)
	{
		for (int x = 0; x <= Game::kScreenWidth - 100; x++)
		{
			//X�̒l�Ɣ�r����
			if (static_cast<int>(m_pos.x) == x)
			{
				m_pos.y = 490 + x * 0.05f;
			}
			m_pos.x = m_pos.x + 1 * 0.005f;
			Reverse = true;

		}
	}
	else if (m_pos.y >= 360)
	{
		for (int x = 160; x <= Game::kScreenWidth; x++)
		{
			//X�̒l�Ɣ�r����
			if (static_cast<int>(m_pos.x) == x)
			{
				m_pos.y = 430 - x * 0.05f;
			}
			m_pos.x = m_pos.x - 1 * 0.005f;
			Reverse = false;

		}
	}
	else if (m_pos.y >= 200)
	{
		for (int x = 0; x <= Game::kScreenWidth - 100; x++)
		{
			//X�̒l�Ɣ�r����
			if (static_cast<int>(m_pos.x) == x)
			{
				m_pos.y = 210 + x * 0.05f;
			}
			m_pos.x = m_pos.x + 1 * 0.005f;
			Reverse = true;

		}
	}
	

	//�c���̈ړ�����
	if (m_pos.y < kGraphHalfHeight )
	{
		m_pos.y = kGraphHalfHeight;
	}
	else if (Game::kScreenHeight - kGraphHalfHeight < m_pos.y)
	{
		m_pos.y = Game::kScreenHeight - kGraphHalfHeight;
	}
	//�����̈ړ�����
	if (m_pos.x < kGraphHalfWidth)
	{
		m_pos.x = kGraphHalfWidth;
	}
	else if (Game::kScreenWidth  - kGraphHalfWidth < m_pos.x)
	{
		m_pos.x = Game::kScreenWidth - kGraphHalfWidth;
	}
	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphHalfWidth, kGraphHalfHeight);

	Time = Time++;
	
	m_Rect.SetCenter(m_pos.x + i, m_pos.y + i, kGraphWidth, kGraphHalfHeight);

	Time++;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
	if (Time == 10)
	{
	}
	}

	//��ʊO�ɏo���瑶�݂�����
	if ((m_pos.x >= 100 && m_pos.y >= 600))
	{
		m_isExist = false;
	}
	
	
}
//�`�揈��
void Enemy::Draw() const
{
	int animeEle = m_walkAnimeFrame / kAnimeFrameNum;

	int scrX = kGraphWidth * kUseFrame[animeEle];
	int scrY = kGraphHeight * m_dir;

	/*DrawBox(m_pos.x - kGraphHalfHeight,
		m_pos.y - kGraphHalfHeight,
		m_pos.x + kGraphHalfWidth,
		m_pos.y + kGraphHalfHeight,
		0xff11ff, true);*/

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		scrX, scrY,
		kGraphWidth, kGraphHeight,
		1.0, 0.0,
		m_handle, true, Reverse);

#ifdef _DEBUG
	m_colRect.Draw(0xff0000, false);
#endif //DEBUG
}

void Enemy::OnFloor(Rect FloorRect)
{
	m_pos.y -= m_MoveDir.y;
}

void Enemy::OnPlayer(Rect PlayerRect)
{
	m_pos.y -= m_MoveDir.y;
}

