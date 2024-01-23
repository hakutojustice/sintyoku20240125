#include"Dxlib.h"
#include <iostream>
#include"Game.h"
#include"Object.h"
#include"Shot.h"
#include "EnemyBase.h"
#include"Player.h"
#include"SceneMain.h"
#include "EnemyToPlayerDir.h"

namespace
{
	constexpr int animDisX = 288;
	constexpr int animDisY = 112;
}


EnemyToPlayerDir::EnemyToPlayerDir():
	m_isDeathFlag(false),
	m_Hp(50),
	m_pos(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	animFrameMana(0, 0),
	m_fireDir(1.0f, 0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0)
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 130;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 75;
}

EnemyToPlayerDir::~EnemyToPlayerDir()
{
}

void EnemyToPlayerDir::Init()
{
	m_handle = LoadGraph("data/image/Enemy/enemyDevilSlime.png");
	m_pos.x = 1300.0;
}

void EnemyToPlayerDir::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 130;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 75;
}

void EnemyToPlayerDir::Update()
{
	m_velocity.y = 0;
	CollisionUpdate();

	
	m_velocity.y += 9.8f;
	m_velocity.x -= 3;
	m_pos += m_velocity;

	if (m_pos.y > Game::kScreenHeight - 130)
	{
		m_pos.y = Game::kScreenHeight - 130;

	}
	if (m_pos.x > Game::kScreenWidth - 75)
	{
		m_pos.x = Game::kScreenWidth - 75;

	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = 0.0f;
	}
}

void EnemyToPlayerDir::Draw()
{
	if (m_isDeathFlag == false)
	{


		DrawRectRotaGraphF(m_pos.x, m_pos.y, 0 + animDisX * animFrameMana.x, 0 + animDisY * animFrameMana.y, 220, 170, 1, 0, m_handle, true);
	}
}

void EnemyToPlayerDir::WantPlayerPoint(Player* player)
{
	m_player = player;
}

void EnemyToPlayerDir::OnHitShot()
{
}

void EnemyToPlayerDir::OnMapCol()
{
	m_velocity.y = 0;
	m_velocity.x = -m_velocity.x;
}

bool EnemyToPlayerDir::OnDie()
{
	return false;
}
