#pragma once
#include "EnemyBase.h"
#include "Point.h"
#include "TimeCount.h"
#include "Player.h"

class Player;
class Shot;
class Point;
class TimeCount;

struct WalkEnemyStruct : public EnemyBase
{
	//�G�̌��ݒn
	float WalkEnemyX = 0.0f; 
    float WalkEnemyY = 0.0f;
	int WalkEnemyGraph = -1;

	//�G�̑傫��
	int WalkEnemyWidth = 20;
	int WalkEnemyHeight = 20;

	//�G�l�~�[�̃X�s�[�h
	float WalkEnemySpeed = 0.04f;
	//�G�l�~�[�̎��S����
	bool WalkEnemyDead = false;
	//�G���e�Ŏ��񂾔���
	bool WalkShotDead = false;

	//�G�l�~�[���o������t���O
	bool WalkEnemyflag = false;
	
};

class WalkEnemy : public EnemyBase
{
public:
	WalkEnemy();
	~WalkEnemy();

	void Init(WalkEnemyStruct enemy[], WalkEnemy& Wenemy, int WenemySize);
	void Update(Player& player, Shot& shot, WalkEnemyStruct enemy[],int WenemySize,float ScrollX,TimeCount* time,WalkEnemy& Wenemy);
	void Draw(float ScrollX, WalkEnemyStruct enemy[], Point& point, int WenemySize);

	EnemyBase Base;
	WalkEnemyStruct WenemyS[ENEMY_NOW];

	//�G�̏o���t���O
	bool WalkEnemyAppearance = true;
	
	//���Ԃ�i�߂�ϐ�
	int T = 0;
};

