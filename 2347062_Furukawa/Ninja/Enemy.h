#pragma once
#include "Rect.h"
#include <memory>

class Map;
class Enemy 
{
public:
	Enemy();
	virtual ~Enemy() {}
	void Update();
	void Draw();


	//�v���C���[�̑�����������Ƃ������W
	float m_x;
	float m_y;

	//�v���C���[�̉����x	1�t���[��������̈ړ���
	float m_moveX;
	float m_moveY;


};

