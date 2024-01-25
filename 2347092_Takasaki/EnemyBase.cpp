#include"Dxlib.h"
#include<vector>
#include <iostream>
#include"Game.h"
#include"Object.h"
#include"Shot.h"
#include "EnemyBase.h"
#include"EneShotEffect.h"
#include"EneShot.h"
#include"Player.h"
#include"SceneMain.h"

namespace
{
	constexpr int animDisX = 288;
	constexpr int animDisY = 112;
}

EnemyBase::EnemyBase() :
	m_isDeathFlag(false),
	m_Hp(50),
	m_pos(500.0f,200.0f),
	m_velocity(0.0f,0.0f),
	animFrameMana(0,0),
	m_fireDir(1.0f,0.0f),
	m_isShotCollFlag(false),
	m_attackFrame(0)
{
	for (auto& shot : m_shot)
	{
		shot = nullptr;
	}
	

	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 130;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 75;

	/*m_shotGraph =  LoadGraph("data/image/eneShot.png") ;

	m_WorldMana = new SceneMain;
	m_player = new Player{ m_WorldMana };
	m_shot = nullptr;*/
}



EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
	m_handle = LoadGraph("data/image/Enemy/enemyDevilSlime.png");
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
	m_shotGraph = LoadGraph("data/image/eneShot.png");
	


}

void EnemyBase::CollisionUpdate()
{
	m_colRect.top = m_pos.y;
	m_colRect.bottom = m_pos.y + 50;
	m_colRect.left = m_pos.x;
	m_colRect.right = m_pos.x + 50;

	
}

void EnemyBase::Update()
{/*
	m_fireDir = m_player->GetPos();
	m_fireDir.x = (m_fireDir.x - m_pos.x) ;
	m_fireDir.y = (m_fireDir.y - m_pos.y) ;
	
	if (m_attackFrame > 60)
	{
		m_shot = new Shot{ m_shotGraph };
		if (m_shot->GetIsDestroy() == true)
		{
			m_fireDir.Normalize();

			m_shot->ShotProgram(m_pos, m_fireDir);
		}
		m_attackFrame = 0;
	}
	*/



	CollisionUpdate();
	

	m_attackFrame++;
	if (m_player != nullptr)
	{
		m_targetPos.x = m_player->GetRect().right+20;
		m_targetPos.y = m_player->GetRect().top + 50;
		m_velocity.x = (m_targetPos.x+40 - m_pos.x)* (m_targetPos.x+40 - m_pos.x);
		m_velocity.y = (m_targetPos.y - m_pos.y)* (m_targetPos.y - m_pos.y);
		m_distance = sqrt(m_velocity.x + m_velocity.y);

		
		if (m_distance < 1000)
		{
			m_fireDir = m_velocity;

			m_fireDir.Normalize();


			for (int i = 0; i < 10; i++)
			{
				if (m_attackFrame >= 60)
				{
					if (m_shot[i] == nullptr)
					{
						m_shotEffect[i] = std::make_shared<EneShotEffect>();
						m_shot[i] = std::make_shared<EneShot>();


						m_pos.x -= m_screenMove;
						m_shot[i]->ShotProgram(m_pos, m_fireDir, m_shotGraph,m_shotEffect[i]);
						m_WorldMana->AddEneShot(m_shot[i]);
						m_attackFrame = 0;
						m_pos.x += m_screenMove;
						break;

					}
				}


			}



			
		}
		for (int i = 0; i < 10; i++)
		{
			if (m_shot[i] != nullptr)
			{
				m_shot[i]->Update();
				if (m_shot[i]->GetIsDestroy())
				{
					m_shotEffect[i] = nullptr;
					m_shot[i] = nullptr;
				}
			}
		}
		/*m_velocity.y = 50;
		m_pos += m_velocity;*/

		if (m_pos.y > Game::kScreenHeight - 130)
		{
			

		}
		if (m_pos.x > Game::kScreenWidth - 75)
		{
			
		
		}
		if (m_pos.y < 0)
		{
			
		}
		if (m_pos.x < 0)
		{
			
		}
	}
		
}



void EnemyBase::Draw()
{
	
	if(m_isDeathFlag==false)
	{
		DrawBox(m_pos.x-m_screenMove, m_pos.y, m_pos.x + 50-m_screenMove, m_pos.y + 50, 0xff0000, true);
		DrawPixel(m_pos.x-m_screenMove + 25, m_pos.y + 25, 0x000000);
		for (int i = 0; i < 10; i++)
		{
			if (m_shot[i] != nullptr)
				m_shot[i]->Draw();
		}
		//DrawRectRotaGraphF(m_pos.x, m_pos.y, 0 + animDisX * animFrameMana.x, 0 + animDisY * animFrameMana.y, 220, 170, 1, 0, m_handle, true);
	}
	
}

void EnemyBase::OnHitShot()
{
	m_Hp -= 10;
	if(m_Hp<0)
	{
		m_isDeathFlag = true;
	}
	
}

void EnemyBase::WantPlayerPoint(Player* player)
{
	m_player = player;
}

void EnemyBase::GetScreenMove(float veloX)
{
	//{ m_pos.x -= veloX; }
}

bool EnemyBase::OnDie()
{
	return m_isDeathFlag;
}
