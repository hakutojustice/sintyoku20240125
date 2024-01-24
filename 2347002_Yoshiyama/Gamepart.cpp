//�Q�[���̃v���C��ʂ̃\�[�X�t�@�C��

//�w�b�_�t�@�C���ǂݍ���
#include "SceneMain.h"
#include "Gamepart.h"
#include "Player.h"
#include "Floor.h"
#include "Enemy.h"

#include "DxLib.h"
#include <cassert>

//�R���X�g���N�^
Gamepart::Gamepart()
{
	//�O���t�B�b�N�̃��[�h
	m_GamePlayerHandle = LoadGraph("data/Player.png");
	assert(m_GamePlayerHandle != -1);
	m_enemyHandle = LoadGraph("data/Enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/Map.png");
	assert(m_bgHandle != -1);
	m_wallHandle = LoadGraph("data/Wall.png");
	assert(m_wallHandle != -1);


	//���̃������m��
	m_pFloor = new Floor;
	m_pFloor->SetHandle(m_wallHandle);
	//�v���C���[�̃������m��
	m_pPlayer = new Player;
	m_pPlayer->SetHandle(m_GamePlayerHandle);
	//�G�̃������̊m��
	m_pEnemy = new Enemy;
	m_pEnemy->SetHandle(m_enemyHandle);
}
//�f�X�g���N�^
Gamepart::~Gamepart()
{
	//�������폜
	DeleteGraph(m_GamePlayerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_wallHandle);

	//���ƃv���C���[�̃������J��
	delete m_pFloor;
	delete m_pPlayer;
	m_pFloor = nullptr;
	m_pPlayer = nullptr;
	//�G�l�~�[�̃������J��
	delete m_pEnemy;
	m_pEnemy = nullptr;
}
//����������
void Gamepart::Init()
{
	m_pFloor->Init();
	m_pPlayer->Init();
	m_pEnemy->Init();
}
//�X�V����
void Gamepart::Update()
{
	if (m_isEnemyhit == false && m_isGoal == false)
	{
		//Floor�̍X�V������ǂݍ���
		m_pFloor->Update();
		//Player�̍X�V������ǂݍ���
		m_pPlayer->Update();
		//Enemy�̍X�V������ǂݍ���
		m_pEnemy->Update();
		//�����蔻��̓ǂݍ���
		Rect playerRect = m_pPlayer->GetColRect();
		Rect floorRect = m_pFloor->GetRect();
		Rect EnemyRect = m_pEnemy->GetColRect();
		//�^�[�Q�b�g�̎w��
		if (playerRect.IsCollsion(floorRect))
		{
			//m_pPlayer->OnFloor(floorRect);
		}
		//�^�[�Q�b�g�̎w��
		if (EnemyRect.IsCollsion(playerRect))
		{
			//m_pPlayer->OnEnemy(EnemyRect);
			m_isEnemyhit = true;
		}

		if (m_pPlayer->GetGoalFlag() == true)
		{
			m_isGoal = true;
		}
	}
}
//�`�揈��
void Gamepart::Draw()
{
	m_pFloor->Draw();
	m_pPlayer->Draw();
	m_pEnemy->Draw();

	Vec2 PlayerPos = m_pPlayer->GetPos();
	Vec2 EnemyPos = m_pEnemy->GetPos();
	DrawFormatString(8, 24, 0xffffff,
		"�v���C���[�̍��W(%.2f,%.2f)", PlayerPos.x, PlayerPos.y);
	DrawFormatString(8, 40, 0xffffff,
		"�G�̍��W(%.2f,%.2f)", EnemyPos.x, EnemyPos.y);

}
