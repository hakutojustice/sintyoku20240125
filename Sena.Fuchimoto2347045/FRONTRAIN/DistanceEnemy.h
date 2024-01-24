#pragma once
#include "EnemyBase.h"
#include "Point.h"
#include "TimeCount.h"
#include "Player.h"
#define ENEMY_SHOT 30

class Player;
class Shot;
class Point;
class TimeCount;
class Shield;

struct EnemyShot
{
	//弾が発射中かどうか
	bool Flag = false;
	//x座標
	double X = 0;
	//y座標
	double Y = 0;
	//グラフィックハンドル
	int Graph = -1;
	//画像の幅と高さ
	int Width = 0;
	int Height = 0;
	//弾が標的に向かっていく
	double PX = 0;
	double PY = 0;
	//弾のダメージ
	int ShotDamage = 2;

	//当たり判定の矩形
	Rect m_colRect;
};

struct DistanceEnemyStruct : public EnemyBase
{
	//敵の現在地
	float DistanceEnemyX = 0.0f;
	float DistanceEnemyY = 0.0f;
	int DistanceEnemyGraph = -1;

	//敵の大きさ
	int DistanceEnemyWidth = 20;
	int DistanceEnemyHeight = 20;

	//敵のスピード
	float DistanceEnemySpeed = 0.02f;
	//敵の死亡判定
	bool DistanceEnemyDead = false;
	//敵が弾で死んだ判定
	bool DistanceShotDead = false;

	//敵が出現するフラグ
	bool DistanceEnemyflag = false;

	//現在時間を得る
	int Time = 0;
	//敵の弾発射までの時間
	int ShotEnemy = 0;
	int ShotDistance = 0;

	//敵が死んだ時のアニメーションフレーム
	int m_DeadAnimFrame;

	//前のフレームで撃ったかどうか
	bool EnemyShotFlag = false;

};
class DistanceEnemy : public EnemyBase
{
public:
	DistanceEnemy();
	~DistanceEnemy();

	void Init(DistanceEnemyStruct& enemy,DistanceEnemy& Denemy);
	void EnemyShotInit(EnemyShot shot[]);
	void Update(Player& player, Shot& shot, DistanceEnemyStruct enemy[], int DenemySize, float ScrollX, TimeCount* time, DistanceEnemy& Denemy, EnemyShot enemyshot[], int EnemyShotSize, Shield& shield);
	void EnemyShotUpdate(DistanceEnemyStruct enemy[], EnemyShot& shot, int enemySize, Player& player, float ScrollX, Shield& shield);
	void Draw(float ScrollX, DistanceEnemyStruct& enemy, Point& point, Player& player, int DownAnimGraph);
	void DrawShot(EnemyShot shot[],int EnemyShotSize,int ScrollX);

	//敵の出現フラグ
	bool DistanceEnemyAppearance = true;

	//時間を進める変数
	int T = 0;
};

