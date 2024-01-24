#include"Dxlib.h"
#include"Game.h"
#include"Object.h"
#include "Shot.h"
#include"Player.h"
#include"EnemyBase.h"
#include<cmath>
#include "CircleShot.h"
#include"ShotEffect.h"


CircleShot::CircleShot():
	m_handle(-1),
	m_shotPos(0, 0),

	m_Velocity(0, 0),
	m_radius(15)
{
}

CircleShot::~CircleShot()
{
}

void CircleShot::Init()
{
	GetGraphSizeF(m_handle, &m_graphSize.x, &m_graphSize.y);
}

void CircleShot::Update()
{
	//collision�̍X�V
	m_collider.pos = m_shotPos; m_collider.radius = m_radius;

	if (m_isVisible == false)
	{
		if (m_shotPos.x >= Game::kScreenWidth)
			m_isVisible = true;
		if (m_shotPos.x <= 0 - m_graphSize.x)
			m_isVisible = true;
		if (m_shotPos.y >= Game::kScreenHeight)
			m_isVisible = true;
		if (m_shotPos.y <= 0 - m_graphSize.y)
			m_isVisible = true;



		/*m_enePos = m_enemy->GetEnePos();
		m_Velocity.x = (m_enePos.x-m_shotPos.x);
		m_Velocity.y = (m_enePos.y- m_shotPos.y);
		m_Velocity.Normalize();*/

		

		m_Velocity.Normalize();
		m_rotateCenter += m_Velocity * 3.0f;

		rotatePos.x = (m_shotPos.x-m_rotateCenter.x)*cos(3.14 / 30)- (m_shotPos.y - m_rotateCenter.y) * sin(3.14 / 30);
		rotatePos.y = (m_shotPos.x - m_rotateCenter.x) * sin(3.14 / 30) + (m_shotPos.y - m_rotateCenter.y) * cos(3.14 / 30);

		

		/*m_shotPos.x = ;
		m_shotPos.y = rotatePos.y * sin(3.14 / 30) + rotatePos.x * cos(3.14 / 15) ;*/

		m_shotPos = rotatePos+m_rotateCenter;
		

	}




}

void CircleShot::Draw()
{
	if (m_isVisible == false)
	{

		DrawGraph(m_shotPos.x, m_shotPos.y, m_handle, true);
	}
}

void CircleShot::ShotProgram(const Vec2& Spos,const Vec2& DirVec,const int& graph)
{
	
	m_isVisible = false;
	m_rotateCenter = Spos;
	m_Velocity = DirVec;
	m_shotPos.x = Spos.x + 5;
	m_shotPos.y = Spos.y + 2;
	m_handle = graph;
}

bool CircleShot::GetShotColli(const Rect& rect)
{
	if (m_isVisible == false)
	{

		if (m_shotPos.y - m_radius <= rect.bottom && m_shotPos.y + m_radius >= rect.top)
		{
			if (m_shotPos.x + m_radius >= rect.left && m_shotPos.x - m_radius <= rect.right)
			{
				m_effect->WantHitPos(this, m_shotPos);

				m_isVisible = true;
				return true;
			}
		}
	}



	return false;
}
