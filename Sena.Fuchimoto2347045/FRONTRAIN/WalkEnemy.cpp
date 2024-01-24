#include "WalkEnemy.h"
#include "DxLib.h"
#include<cmath>


WalkEnemy::WalkEnemy()
{
}

WalkEnemy::~WalkEnemy()
{
}

void WalkEnemy::Init(WalkEnemyStruct enemy[], WalkEnemy& Wenemy,int WenemySize)
{
	for (int i = 0; i < WenemySize; i++)
	{
		enemy[i].WalkEnemyX = -30.0f;
		enemy[i].WalkEnemyY = -30.0f;

		enemy[i].WalkEnemyDead = false;

		enemy[i].WalkShotDead = false;

		enemy[i].WalkEnemyflag = false;

		enemy[i].WalkEnemyGraph = LoadGraph("date/エネミー(仮).png");
	}

	Wenemy.Attack = 2;

	Wenemy.HP = 10;

	Wenemy.WalkEnemyAppearance = true;

	Wenemy.T = 0;

}

void WalkEnemy::Update(Player& player,Shot& shot,WalkEnemyStruct enemy[],int WenemySize, float ScrollX, TimeCount* time, WalkEnemy& Wenemy)
{
	//時間がたつと敵が出現
	if (time->EnemyTime == 10 + (6 * Wenemy.T))
	{
		if (Wenemy.WalkEnemyAppearance == true)
		{
			Wenemy.T++;

			for (int i = 0; i < WenemySize; i++)
			{
				if (enemy[i].WalkEnemyflag == false)
				{
					enemy[i].WalkEnemyDead = false;

					enemy[i].WalkEnemyflag = true;

					//エネミーがランダムな場所に出現
					if (GetRand(1) == 0)
					{
						enemy[i].WalkEnemyX = -40.0f - ScrollX;
					}
					if (GetRand(1) == 1)
					{
						enemy[i].WalkEnemyX = 680.0f - ScrollX;
					}

					enemy[i].WalkEnemyY = 360.0f;

					//一体だしたのでループから抜ける
					break;
				}

			}
			Wenemy.WalkEnemyAppearance = false;
		}

	}
	else
	{
		Wenemy.WalkEnemyAppearance = true;
	}

	for (int i = 0; i < WenemySize; i++)
	{
		if (enemy[i].WalkEnemyflag == true)
		{
			//エネミーが生きている時
			if (enemy[i].HP >= 0)
			{

				//敵の移動処理
				if (player.PlayerX - player.ScrollX <= enemy[i].WalkEnemyX)
				{
					enemy[i].WalkEnemyX -= enemy[i].WalkEnemySpeed;
				}
				else if (player.PlayerX - player.ScrollX > enemy[i].WalkEnemyX)
				{
					enemy[i].WalkEnemyX += enemy[i].WalkEnemySpeed;
				}

				//当たり判定の更新
				enemy[i].m_colRect.SetCenter(enemy[i].WalkEnemyX + 10 + player.ScrollX, enemy[i].WalkEnemyY + 10, enemy[i].WalkEnemyWidth, enemy[i].WalkEnemyHeight);

				//プレイヤーの当たり判定
				if (enemy[i].m_colRect.IsCollision(player.m_colRect) == false)
				{
					//当たってない
				}
				//当たっている
				else if (enemy[i].m_colRect.IsCollision(player.m_colRect) == true)
				{
					//1回だけ実行
					if (player.PlayerDamage == false)
					{
						player.HP -= Wenemy.Attack;

						player.PlayerDamage = true;
					}

					enemy[i].HP = -1;
					
				}

				if (shot.Flag == 1)
				{
					//敵との当たり判定
					if (enemy[i].m_colRect.IsCollision(shot.m_colRect) == false)
					{

					}
					else if (enemy[i].m_colRect.IsCollision(shot.m_colRect) == true)
					{
						enemy[i].HP -= shot.Damage;
						//接触している場合は当たった弾の存在を消す
						shot.Flag = 0;

						enemy[i].WalkShotDead = true;

						//DeleteGraph(shot.Graph);
					}

				}
			}

		}
	}
	
}

void WalkEnemy::Draw(float ScrollX,WalkEnemyStruct enemy[], Point& point,int WenemySize)
{
	for (int i = 0; i < WenemySize; i++)
	{
		//エネミーが生きている時
		if (enemy[i].HP > 0)
		{
			DrawGraph(enemy[i].WalkEnemyX + ScrollX, enemy[i].WalkEnemyY, enemy[i].WalkEnemyGraph, true);

			//エネミーの当たり判定の表示
			enemy[i].m_colRect.Draw(GetColor(255, 0, 0), false);
		}
		//敵が死んだ時
		else if (enemy[i].HP <= 0)
		{
			if (enemy[i].WalkEnemyDead == false)
			{
				enemy[i].m_colRect.SetCenter(0, 0, 0, 0);
				if (enemy[i].WalkShotDead == true)
				{
					point.WenemyPoint += 100;

					enemy[i].WalkShotDead = false;
				}

				enemy[i].WalkEnemyflag = false;

				enemy[i].HP = 10;

				enemy[i].WalkEnemyX = -30.0f;
				enemy[i].WalkEnemyY = -30.0f;

				enemy[i].WalkEnemyDead = true;
			}

		}
	}
	
	
}
