#pragma once

#include "Rect.h"
#include "Enemy.h"
#include <memory>

class Map;
class Enemy;
class Player
{
public:
	Player();
	virtual ~Player() {}


	void Update(Enemy& enemy);
	void Draw();


private:

	//�W�����v
	float m_isJump;

	//�v���C���[�̑�����������Ƃ������W
	float m_x;
	float m_y;

	//�v���C���[�̉����x	1�t���[��������̈ړ���
	float m_moveX;
	float m_moveY;

	float m_damage;

	float PlayerFlog;

	//�v���C���[�̕`��
	//float PlayerGraph;
};
