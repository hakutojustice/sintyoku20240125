#pragma once
#include "Rect.h"
#define ENEMY_NOW 15
#define SKY_ENEMY_NOW 15
#define DISTANCE_ENEMY_NOW 10

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	int HP;
	int Speed;
	int Attack;
	int EnemyW;
	int EnemyH;

	//�����蔻��̋�`
	Rect m_colRect;
};

