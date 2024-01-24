#include "Enemy.h"
#include"DxLib.h"
#include "BaseNumber.h"
#include "Character.h"
#include <cmath>


void Enemy::InitEnemy()
{
	

}


void Enemy::Draw()
{
	int EnemyHandle=LoadGraph("RoperMan.png");
	
	for (int y = 0; y < EnemyChipY; y++)
	{
		for (int x = 0; x < EnemyChipX; x++)
		{
			if (MakeEnemy[y][x]==1)
			{
				DrawRectGraph(enemyX, enemyY, EnemyPerChraSize, EnemyPerChraSize, EnemyPerChraSize,EnemyPerChraSize, EnemyHandle, true);
				
			}
		}
	}
	
}


void Enemy::KillerRabbit(Character& e_chara)
{
	
	int EnemyHandle2 = LoadGraph("pyon-manjiro1.png");
	DrawRectGraph(RabbitX,RabbitY, EnemyPerChraSize, EnemyPerChraSize, EnemyPerChraSize, EnemyPerChraSize, EnemyHandle2, true);



}

void Enemy::EnemyMove() 
{
	
	--enemyX;
	--RabbitY;
	--RabbitX;

	
	
	

}

void Enemy::EnemyWallBumped()
{

	if (enemyX < 0)
	{
		enemyX = 0;


	}
	if (enemyX > 608)
	{
		enemyX = 608;

	}
	if (RabbitX<0)
	{
		RabbitX = 0;
	}
	if (RabbitY < 0)
	{
		RabbitY = 0;
	}



}

void Enemy::EnemyAirCollision(Character& e_chara)
{
	if (RabbitX-e_chara.Player_posX<16&&RabbitX>e_chara.Player_posX)
	{
		GraphFilter(e_chara.PlayerHandle ,DX_GRAPH_FILTER_MONO);
	}


}





