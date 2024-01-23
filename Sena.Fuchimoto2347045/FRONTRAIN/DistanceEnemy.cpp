#include "DistanceEnemy.h"
#include "DxLib.h"
#include<cmath>
#include<math.h>

//DisEnemyで使用するアニメーション定数
namespace
{
	//画像サイズ
	int kWidth = 30;
	int kHeight = 30;

	//キャラクター1コマのフレーム数
	constexpr int kAnimFrameNum = 8;

	//キャラクターがやられた時のアニメーション
	constexpr int kUseDownFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	//アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseDownFrame) * kAnimFrameNum;

}

DistanceEnemy::DistanceEnemy()
{
}

DistanceEnemy::~DistanceEnemy()
{
}

void DistanceEnemy::Init(DistanceEnemyStruct& enemy, DistanceEnemy& Denemy)
{
	Denemy.Attack = 2;
	Denemy.HP = 5;

	enemy.DistanceEnemyX = -30.0f;
	enemy.DistanceEnemyY = -30.0f;

	enemy.DistanceEnemyDead = false;

	enemy.DistanceShotDead = false;

	enemy.DistanceEnemyflag = false;

	Denemy.DistanceEnemyAppearance = true;

	Denemy.T = 0;

	enemy.Time = 0;

	enemy.ShotEnemy = 0;
	enemy.ShotDistance = 1;

	enemy.EnemyShotFlag = true;

	enemy.m_DeadAnimFrame;

	enemy.DistanceEnemyGraph = LoadGraph("date/DistanceEnemy.png");
}

void DistanceEnemy::EnemyShotInit(EnemyShot shot[])
{
	for (int i = 0; i < ENEMY_SHOT; i++)
	{
		shot[i].Flag = false;

		shot[i].ShotDamage = 2;
	}
}

void DistanceEnemy::Update(Player& player, Shot& shot, DistanceEnemyStruct enemy[], int DenemySize, float ScrollX, TimeCount* time, DistanceEnemy& Denemy,EnemyShot enemyshot[],int EnemyShotSize,Shield& shield)
{
	//時間がたつと敵が出現
	if (time->EnemyTime == 360 + (10 * Denemy.T))
	{
		if (Denemy.DistanceEnemyAppearance == true)
		{
			Denemy.T++;

			for (int i = 0; i < DenemySize; i++)
			{
				if (enemy[i].DistanceEnemyflag == false)
				{
					//現在時間を得る
					enemy[i].Time = GetNowCount();

					enemy[i].DistanceEnemyDead = false;

					enemy[i].DistanceEnemyflag = true;

					//エネミーがランダムな場所に出現
					if (GetRand(1) == 0)
					{
						enemy[i].DistanceEnemyX = -40.0f - ScrollX;
					}
					if (GetRand(1) == 1)
					{
						enemy[i].DistanceEnemyX = 680.0f - ScrollX;
					}

					enemy[i].DistanceEnemyY = 360.0f;

					//一体だしたのでループから抜ける
					break;
				}
			}
			Denemy.DistanceEnemyAppearance = false;
		}
	}
	else
	{
		Denemy.DistanceEnemyAppearance = true;
	}

	for (int i = 0; i < DenemySize; i++)
	{
		if (enemy[i].DistanceEnemyflag == true)
		{
			//敵が生きている時
			if (enemy[i].HP >= 0)
			{
				//敵の移動処理
				//右から
				if (player.PlayerX - player.ScrollX + 200 < enemy[i].DistanceEnemyX)
				{
					enemy[i].DistanceEnemyX -= enemy[i].DistanceEnemySpeed;
				}
				//右に逃げる
				else if (player.PlayerX - player.ScrollX + 200 > enemy[i].DistanceEnemyX && player.PlayerX - player.ScrollX < enemy[i].DistanceEnemyX)
				{
					enemy[i].DistanceEnemyX += enemy[i].DistanceEnemySpeed;
				}
				//左から
				if (player.PlayerX - player.ScrollX - 150 > enemy[i].DistanceEnemyX)
				{
					enemy[i].DistanceEnemyX += enemy[i].DistanceEnemySpeed;
				}
				//左に逃げる
				else if (player.PlayerX - player.ScrollX - 150 < enemy[i].DistanceEnemyX && player.PlayerX - player.ScrollX > enemy[i].DistanceEnemyX)
				{
					enemy[i].DistanceEnemyX -= enemy[i].DistanceEnemySpeed;
			
				}

				//敵の攻撃行動
				enemy[i].ShotEnemy = (GetNowCount() - enemy[i].Time) / 1000;

				if (enemy[i].ShotEnemy == 4 * enemy[i].ShotDistance)
				{
					enemy[i].EnemyShotFlag = false;

					for (int j = 0; j < EnemyShotSize; j++)
					{
						enemyshot[j].Flag = false;
					}

					enemy[i].ShotDistance++;
				}



				//当たり判定の更新
				enemy[i].m_colRect.SetCenter(enemy[i].DistanceEnemyX + 10 + player.ScrollX, enemy[i].DistanceEnemyY + 10, enemy[i].DistanceEnemyWidth, enemy[i].DistanceEnemyHeight);

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
						player.HP -= Denemy.Attack;

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
						//1回だけ実行
						if (player.PlayerDamage == false)
						{
							enemy[i].HP -= shot.Damage;

							player.PlayerDamage = true;
						}
						
						//接触している場合は当たった弾の存在を消す
						shot.Flag = 0;

						enemy[i].DistanceShotDead = true;

					}

				}
			}
			
		}
	}
}

//敵の攻撃行動
void DistanceEnemy::EnemyShotUpdate(DistanceEnemyStruct enemy[], EnemyShot& shot, int enemySize, Player& player, float ScrollX, Shield& shield)
{
	for (int i = 0; i < enemySize; i++)
	{
		if (enemy[i].EnemyShotFlag == false)
		{
			if (shot.Flag == false)
			{
				shot.Flag = true;
				shot.X = enemy[i].DistanceEnemyX;
				shot.Y = enemy[i].DistanceEnemyY + enemy[i].DistanceEnemyHeight / 2;

				//弾の移動速度を設定する
				double sb, sbx, sby, ax, ay, sx, sy;

				sx = shot.X;
				sy = shot.Y;

				//標的の場所
				ax = player.PlayerX - ScrollX;
				ay = player.PlayerY;

				sbx = ax - sx;
				sby = ay - sy;

				sb = sqrt(sbx * sbx + sby * sby);

				//1フレームあたり10ドットで動く
				shot.PX = sbx / sb * 5;
				shot.PY = sby / sb * 5;

				//一つ弾を出したので弾を出すループから抜ける
				break;
			}
		}
	    enemy[i].EnemyShotFlag = true;
	}

	if (shot.Flag == 1)
	{

		//盾との接触判定
		if (shield.LeftFlag == true || shield.RightFlag == true)
		{
			//盾との当たり判定
			if (shot.m_colRect.IsCollision(shield.m_colRect) == false)
			{
				//当たってない

			}
			else if (shot.m_colRect.IsCollision(shield.m_colRect) == true)
			{
				DeleteGraph(shot.Graph);

				//接触した弾の存在を消す
				shot.Flag = 0;
			}
		}


		//プレイヤーとの当たり判定
		if (shot.m_colRect.IsCollision(player.m_colRect) == false)
		{

		}
		else if (shot.m_colRect.IsCollision(player.m_colRect) == true)
		{
			player.HP -= shot.ShotDamage;

			DeleteGraph(shot.Graph);

			//接触している場合は当たった弾の存在を消す
			shot.Flag = 0;
		}

	}
}

void DistanceEnemy::Draw(float ScrollX, DistanceEnemyStruct& enemy, Point& point, Player& player,int DownAnimGraph)
{
	//エネミーが生きている時
	if (enemy.HP >= 0)
	{
		if (enemy.DistanceEnemyX + ScrollX > player.PlayerX)
		{
			DrawGraph(enemy.DistanceEnemyX + ScrollX, enemy.DistanceEnemyY - 3, enemy.DistanceEnemyGraph, true);
		}
		else if (enemy.DistanceEnemyX + ScrollX < player.PlayerX)
		{
			DrawTurnGraph(enemy.DistanceEnemyX + ScrollX, enemy.DistanceEnemyY - 3, enemy.DistanceEnemyGraph, true);
		}

		//エネミーの当たり判定の表示
		enemy.m_colRect.Draw(GetColor(255, 0, 0), false);
	}
	//敵が死んだ時
	else if (enemy.HP <= 0)
	{
		if (enemy.HP <= 0)
		{
			//死んだアニメーション
			enemy.m_DeadAnimFrame++;
			if (enemy.m_DeadAnimFrame >= kAnimFrameCycle) enemy.m_DeadAnimFrame = 0;
		}
		else
		{
			enemy.m_DeadAnimFrame = kAnimFrameNum;
		}

		int animFrame = enemy.m_DeadAnimFrame / kAnimFrameNum;

		int srcX = kUseDownFrame[animFrame] * kWidth;
		int srcY = kHeight * 0;

		if (enemy.DistanceEnemyDead == false)
		{
			if (enemy.DistanceShotDead == true)
			{
				point.DenemyPoint += 120;

				enemy.DistanceShotDead = false;
			}
			
			enemy.DistanceEnemyflag = false;

			/*DrawRectRotaGraph(static_cast<int>(enemy.DistanceEnemyX), static_cast<int>(enemy.DistanceEnemyY)
				, srcX, srcY, kWidth, kHeight, 1.0, 0.0, DownAnimGraph, true, false);*/

			enemy.HP = 5;

			enemy.DistanceEnemyX = -30.0f;
			enemy.DistanceEnemyY = -30.0f;

			enemy.DistanceEnemyDead = true;
		}

	}
}

void DistanceEnemy::DrawShot(EnemyShot shot[],int EnemyShotSize,int ScrollX)
{
	//弾の移動
	//発射してる弾数だけ
	for (int i = 0; i < EnemyShotSize; i++)
	{
		if (shot[i].Flag)
		{
			shot[i].Graph = LoadGraph("date/銃弾.png");

			shot[i].X += shot[i].PX;
			shot[i].Y += shot[i].PY;

			DrawGraph(shot[i].X + ScrollX, shot[i].Y, shot[i].Graph, true);

			//あたり判定の更新
			shot[i].m_colRect.SetCenter(shot[i].X + ScrollX, shot[i].Y, shot[i].Width, shot[i].Height);

			//画面上に行きすぎたら消す
			if (shot[i].Y <= -10)
			{
				shot[i].Flag = false;

				DeleteGraph(shot[i].Graph);
			}


		}
	}
	
}
