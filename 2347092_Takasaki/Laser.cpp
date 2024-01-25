#include"Dxlib.h"
#include"Game.h"
#include "Laser.h"

Laser::Laser()
{
}

Laser::~Laser()
{
}

void Laser::Update()
{
	if (m_isVisible == false)
	{

		

		m_laserHead += m_dirVec * 20;

		if (m_laserTail.x >= Game::kScreenWidth)
			m_isVisible = true;
		if (m_laserTail.x <= 0)
			m_isVisible = true;
		if (m_laserTail.y >= Game::kScreenHeight)
			m_isVisible = true;
		if (m_laserTail.y <= 0)
			m_isVisible = true;
		if (sqrtf((m_laserHead.x - m_startPos.x) * (m_laserHead.x - m_startPos.x) + (m_laserHead.y - m_startPos.y) * (m_laserHead.y - m_startPos.y)) > 200)
		{
			m_laserTail += m_dirVec * 20;
		}
	}
	m_limitTime++;
	/*if (sqrtf((m_laserHead.x-m_startPos.x)* (m_laserHead.x-m_startPos.x)+ (m_laserHead.y - m_startPos.y) * (m_laserHead.y - m_startPos.y))>500)
	{
		m_isVisible = true;
	}*/
}

void Laser::Draw()
{
	if(!m_isVisible)
	{
		
		DrawLine(m_laserTail.x, m_laserTail.y,
					 m_laserHead.x, m_laserHead.y, 0xff0000,7);
			
	}
	
}

void Laser::ShotProgram(Vec2 Spos, Vec2 DirVec)
{
	m_startPos = Spos;
	m_dirVec = DirVec;
	m_expLine = DirVec;
	
	b = m_expLine.x / m_expLine.y;
	if (m_expLine.y == 0)
	{
		m_expLine.y = Spos.y;
		b = Spos.y;
	}
	else if (m_expLine.y > 0)
	{
		m_expLine.x = m_expLine.x / m_expLine.y;
		m_expLine.y = 1;
		b = Spos.y - m_expLine.x * Spos.x;//y=ax+b --> y-ax=b(����y����֐��ɏ���x���������������Đؕ�(x=0�̎���y���W�̂���)�����߂�)
	}
	else
	{
		m_expLine.x = m_expLine.x / m_expLine.y;
		m_expLine.y = -1;
		b = Spos.y - m_expLine.x * Spos.x;//����y����֐��ɏ���x���������������Đؕ�(x=0�̎���y���W�̂���)�����߂�
		
	}
	
	m_dirVec.Normalize();
	m_laserTail = m_startPos;
	m_laserHead = m_startPos;
	m_isVisible = false;
}

bool Laser::LineCollider(float x1, float y1, float x2, float y2)
{
	//�l�����͕Е��̐����̎n�_(x1,y1)��y1�����[�U�[�̒���.y���傫�����A�I�_��y���W�̊֌W�����t�ɂȂ��Ă����ꍇ������Ă�(�x�X�̏������t�̏ꍇ��)
	if (m_expLine.x * x1 + b < y1)
	{
		if (m_expLine.x * x2 + b < y2)//����邱�Ƃ��m��
		{
			float b = y1 - ((x1 - x2) / (y1 - y2)) * x1;//�ؕ�


		}
	}






	/*{
		const float baseX = m_laserHead.x - m_laserTail.x;
		const float baseY = m_laserHead .y - m_laserTail.y;
		const float sub1X = m_laserTail.x - x1;
		const float sub1Y = m_laserTail.y - y1;
		const float sub2X = m_laserHead.x - x1;
		const float sub2Y = m_laserHead.y - y1;

		const float bs1 = baseX * sub1Y - baseY * sub1X;
		const float bs2 = baseX * sub2Y - baseY * sub2X;
		const float re = bs1 * bs2;
		if (re > 0) {
			return false;
		}
	}
	{
	const float baseX = m_laserHead.x - m_laserTail.x;
	const float baseY = m_laserHead.y - m_laserTail.y;
	const float sub1X = x1 - m_laserTail.x;
	const float sub1Y = y1 - m_laserTail.y;
	const float sub2X = x2 - m_laserTail.x;
	const float sub2Y = y2 - m_laserTail.y;

	const float bs1 = baseX * sub1Y - baseY * sub1X;
	const float bs2 = baseX * sub2Y - baseY * sub2X;
	const float re = bs1 * bs2;
	if (re > 0) {
		return false;
	}
}
return true;
	*/
	return false;
}



bool Laser::OnLaserCollision(Rect rect)
{
	if (LineCollider(rect.left, rect.top, rect.right, rect.top))return true;
	if (LineCollider(rect.right, rect.top, rect.right, rect.bottom))return true;
	if (LineCollider(rect.right, rect.bottom, rect.left, rect.bottom))return true;
	if (LineCollider(rect.left, rect.bottom, rect.left, rect.top))return true;

	return false;
}

float Laser::toEquation(float& pos1X, float& pos1Y, float& pos2X, float& pos2Y)
{
	

	

	return b;
}











