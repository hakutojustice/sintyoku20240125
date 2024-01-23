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
	//敵の現在地
	float WalkEnemyX = 0.0f; 
    float WalkEnemyY = 0.0f;
	int WalkEnemyGraph = -1;

	//敵の大きさ
	int WalkEnemyWidth = 20;
	int WalkEnemyHeight = 20;

	//エネミーのスピード
	float WalkEnemySpeed = 0.04f;
	//エネミーの死亡判定
	bool WalkEnemyDead = false;
	//敵が弾で死んだ判定
	bool WalkShotDead = false;

	//エネミーが出現するフラグ
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

	//敵の出現フラグ
	bool WalkEnemyAppearance = true;
	
	//時間を進める変数
	int T = 0;
};

