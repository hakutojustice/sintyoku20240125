#pragma once
#include "Player.h"

class Player;

class Point
{
public:
	Point();
	~Point();

	void InitPoint();
	void UpdatePoint(Player& player, int ScrollX);
	void DrawPoint(Player& player, int ScrollX);

	int PointNow, WenemyPoint,SenemyPoint,DenemyPoint;

	//�v���C���[�̈ړ������|�C���g���Z�敪
	int PlayerMove = 0;

	//�v���C���[�̈ړ������ɉ����ă|�C���g�����Z
	int MovePoint = 0;

	//�G�l�~�[�̏o������
	int WalkEnemyTime = 0;
};

