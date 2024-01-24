#pragma once
#include "EnemyBase.h"
#include "Point.h"
#include "TimeCount.h"
#include "Player.h"

class Player;
class Shot;
class Point;
class TimeCount;
class Shield;

struct SkyEnemyStruct : public EnemyBase
{
	//敵の現在地
	float SkyEnemyX = 0.0f;
	float SkyEnemyY = 0.0f;
	int SkyHandle[3];

	//アニメーション画像表示の変数
	int S = 0;

	int Time = 0;

	//敵の大きさ
	int SkyEnemyWidth = 15;
	int SkyEnemyHeight = 10;

	//敵がプレイヤーに向かっていく
	double PX = 0;
	double PY = 0;

	//敵が発生中かどうか
	bool Flag = false;

	//敵の死亡判定
	bool SkyEnemyDead = false;
	//敵が弾で死んだ判定
	bool SkyShotDead = false;

	//敵が出現するフラグ
	bool SkyEnemyflag = false;
};

class SkyEnemy : public EnemyBase
{
public:
	SkyEnemy();
	~SkyEnemy();

	void Init(SkyEnemyStruct& enemy, SkyEnemy& Senemy);
	void Update(Player& player, Shot& shot, SkyEnemyStruct enemy[], int SenemySize, float ScrollX, TimeCount* time, SkyEnemy& Senemy, Shield& shield);
	void Draw(float ScrollX, SkyEnemyStruct& enemy, Point& point);

	//敵の出現フラグ
	bool SkyEnemyAppearance = true;

	

	//時間を進める変数
	int T = 0;
};

