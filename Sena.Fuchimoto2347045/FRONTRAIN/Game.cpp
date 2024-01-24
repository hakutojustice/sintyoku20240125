#include "Game.h"
#include "Player.h"
#include "WalkEnemy.h"
#include "Background.h"
#include "DxLib.h"
#include "Map.h"
#include "GraphMode.h"
#include "TimeCount.h"
#include "Point.h"
#include "SceneMgr.h"
#include "HP.h"
#include "SkyEnemy.h"
#include "DistanceEnemy.h"
#include "SceneFedo.h"

Player player;
HP hp;
Shot shot[SHOT];
Shield shield;
EnemyShot enemyshot[ENEMY_SHOT];

WalkEnemy WEnemy;
WalkEnemyStruct WenemyS[ENEMY_NOW];

SkyEnemy SEnemy;
SkyEnemyStruct SenemyS[SKY_ENEMY_NOW];

DistanceEnemy DEnemy;
DistanceEnemyStruct DenemyS[DISTANCE_ENEMY_NOW];

Map map;
Background Back;
TimeCount timecount;
Point point;

SceneFedo scenefedo;

bool Isflag = false;

int DistanceDown = -1;

//初期化
void Game_Initialize()
{
	Back.Init();

	timecount.InitTime();
	point.InitPoint();
	player.Init(shield, shot);

	player.InitShot(shot);

	DEnemy.EnemyShotInit(enemyshot);

	WEnemy.Init(WenemyS, WEnemy, ENEMY_NOW);

	for (int i = 0; i < SKY_ENEMY_NOW; i++)
	{
		SEnemy.Init(SenemyS[i], SEnemy);
	}
	for (int i = 0; i < DISTANCE_ENEMY_NOW; i++)
	{
		DEnemy.Init(DenemyS[i], DEnemy);
	}
	map.InitMap();

	DistanceDown = LoadGraph("date/爆発Down.png");
}

//終了処理
void Game_Finalize()
{
}

//更新処理
void Game_Update()
{
	scenefedo.UpdateIn();

	timecount.UpdateTime(point);

	point.UpdatePoint(player, player.ScrollX);

	player.Update(player, map, shield);

	for (int i = 0; i < SHOT; i++)
	{
		WEnemy.Update(player, shot[i], WenemyS, ENEMY_NOW, player.ScrollX, &timecount, WEnemy);

		SEnemy.Update(player, shot[i], SenemyS, SKY_ENEMY_NOW, player.ScrollX, &timecount, SEnemy, shield);

		DEnemy.Update(player, shot[i], DenemyS, DISTANCE_ENEMY_NOW, player.ScrollX, &timecount, DEnemy, enemyshot, ENEMY_SHOT, shield);
	}
	for (int j = 0; j < ENEMY_SHOT; j++)
	{
		DEnemy.EnemyShotUpdate(DenemyS, enemyshot[j], DISTANCE_ENEMY_NOW, player, player.ScrollX, shield);
	}
	
	

	player.ShotUpdate(player, shot, SHOT);
	map.UpdateMap(player.ScrollX);

	//プレイヤーが死亡すると
	if (player.HP <= 0)
	{
		scenefedo.DeadOut();

		SceneMgr_ChageScene(eScene_GameOver);//シーンをゲームオーバー画面に変更
	}
}

//描画処理
void Game_Draw()
{
	Back.Draw();

	timecount.DrawTime();
	point.DrawPoint(player, player.ScrollX);

	hp.PlayerHP(player);

	player.Draw(shield, player);
	
	for (int i = 0; i < SHOT; i++)
	{
		player.DrawShot(shot[i]);
	}

	DEnemy.DrawShot(enemyshot, ENEMY_SHOT, player.ScrollX);


	WEnemy.Draw(player.ScrollX, WenemyS, point, ENEMY_NOW);

	for (int i = 0; i < SKY_ENEMY_NOW; i++)
	{
		SEnemy.Draw(player.ScrollX, SenemyS[i], point);
	}
	for (int i = 0; i < DISTANCE_ENEMY_NOW; i++)
	{
		DEnemy.Draw(player.ScrollX, DenemyS[i], point, player, DistanceDown);
	}

	for (int i = 0; i < SHOT; i++)
	{
		map.DrawMap(player.ScrollX, shot[i], player, WenemyS, SenemyS, DenemyS, enemyshot,ENEMY_SHOT);
	}

	
}
