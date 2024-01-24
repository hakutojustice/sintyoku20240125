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

	//プレイヤーの移動距離ポイント加算区分
	int PlayerMove = 0;

	//プレイヤーの移動距離に応じてポイントを加算
	int MovePoint = 0;

	//エネミーの出現時間
	int WalkEnemyTime = 0;
};

