#include "SkyEnemy.h"
#include "DxLib.h"
#include<cmath>
#include<math.h>

SkyEnemy::SkyEnemy()
{
}

SkyEnemy::~SkyEnemy()
{
}

void SkyEnemy::Init(SkyEnemyStruct& enemy, SkyEnemy& Senemy)
{
	Senemy.Attack = 1;
	Senemy.HP = 1;
	
	enemy.SkyEnemyX = 0.0f;
	enemy.SkyEnemyY = 0.0f;

	enemy.SkyEnemyDead = false;

	enemy.SkyShotDead = false;

	enemy.SkyEnemyflag = false;

	Senemy.SkyEnemyAppearance = true;

	Senemy.T = 0;

	enemy.S = 0;

	enemy.Time = 0;

	LoadDivGraph("date/SkyEnemy.png", 3, 3, 1, 15, 20, enemy.SkyHandle);

}

void SkyEnemy::Update(Player& player,Shot& shot, SkyEnemyStruct enemy[], int SenemySize, float ScrollX, TimeCount* time, SkyEnemy& Senemy,Shield& shield)
{
	//“G‚ÌƒXƒs[ƒhÝ’è
	double tb, tbx, tby, px, py, sx, sy;

	//ŽžŠÔ‚ª‚½‚Â‚Æ“G‚ªoŒ»
	if (time->EnemyTime == 180 +  (3 * Senemy.T))
	{
		if (Senemy.SkyEnemyAppearance == true)
		{
			Senemy.T++;

			for (int i = 0; i < SenemySize; i++)
			{
				if (enemy[i].SkyEnemyflag == false)
				{
					enemy[i].SkyEnemyDead = false;

					enemy[i].Flag = false;

					enemy[i].SkyEnemyflag = true;

					//ƒGƒlƒ~[‚ªƒ‰ƒ“ƒ_ƒ€‚ÈêŠ‚ÉoŒ»
					
					enemy[i].SkyEnemyX = GetRand(640) - ScrollX;

					enemy[i].SkyEnemyY = -10.0f;

					//ˆê‘Ì‚¾‚µ‚½‚Ì‚Åƒ‹[ƒv‚©‚ç”²‚¯‚é
					break;
				}
			}
			Senemy.SkyEnemyAppearance = false;
		}
	}
	else
	{
		Senemy.SkyEnemyAppearance = true;
	}

	for (int i = 0; i < SenemySize; i++)
	{
		if (enemy[i].SkyEnemyflag == true)
		{
			//“G‚ª¶‚«‚Ä‚¢‚éŽž
			if (enemy[i].HP >= 0)
			{
				if (enemy[i].Flag == false)
				{
					enemy[i].Flag = true;
					//“G‚ÌˆÚ“®ˆ—
					sx = enemy[i].SkyEnemyX + enemy[i].SkyEnemyWidth / 2;
					sy = enemy[i].SkyEnemyY + enemy[i].SkyEnemyHeight / 2;
					px = player.PlayerX - ScrollX + player.PlayerWidth / 2;
					py = player.PlayerY + player.PlayerHeight / 2;

					tbx = px - sx;
					tby = py - sy;

					tb = sqrt(tbx * tbx + tby * tby);

					//1ƒtƒŒ[ƒ€‚ ‚½‚è7ƒhƒbƒg‚Å“®‚­
					enemy[i].PX = tbx / tb * 7;
					enemy[i].PY = tby / tb * 7;

					//ˆê‘Ì‚¾‚µ‚½‚Ì‚Å”²‚¯‚é
					break;
				}
				
			}

			//“–‚½‚è”»’è‚ÌXV
			enemy[i].m_colRect.SetCenter(enemy[i].SkyEnemyX + 7 + player.ScrollX, enemy[i].SkyEnemyY + 10, enemy[i].SkyEnemyWidth, enemy[i].SkyEnemyHeight);

			//ƒvƒŒƒCƒ„[‚Ì“–‚½‚è”»’è
			if (enemy[i].m_colRect.IsCollision(player.m_colRect) == false)
			{
				//“–‚½‚Á‚Ä‚È‚¢
			}
			//“–‚½‚Á‚Ä‚¢‚é
			else if (enemy[i].m_colRect.IsCollision(player.m_colRect) == true)
			{
				//1‰ñ‚¾‚¯ŽÀs
				if (player.PlayerDamage == false)
				{
					player.HP -= Senemy.Attack;

					player.PlayerDamage = true;
				}
				

				enemy[i].HP = -1;
			}

			if (shot.Flag == 1)
			{
				//“G‚Æ‚Ì“–‚½‚è”»’è
				if (enemy[i].m_colRect.IsCollision(shot.m_colRect) == false)
				{
					//“–‚½‚Á‚Ä‚È‚¢
				}
				else if (enemy[i].m_colRect.IsCollision(shot.m_colRect) == true)
				{
					enemy[i].HP -= shot.Damage;
					//ÚG‚µ‚Ä‚¢‚éê‡‚Í“–‚½‚Á‚½’e‚Ì‘¶Ý‚ðÁ‚·
					shot.Flag = 0;

					enemy[i].SkyShotDead = true;

				}
			}
			//‚‚Æ‚Ì“–‚½‚è”»’è
			if (shield.LeftFlag == true || shield.RightFlag == true)
			{
				//‚‚ÆÚG
				if (enemy[i].m_colRect.IsCollision(shield.m_colRect) == false)
				{
					//“–‚½‚Á‚Ä‚È‚¢
				}
				else if (enemy[i].m_colRect.IsCollision(shield.m_colRect) == true)
				{
					//‚‚É“–‚½‚Á‚½‚çŽ€‚Ê
					enemy[i].HP = -1;
				}
			}


		}
	}

}

void SkyEnemy::Draw(float ScrollX, SkyEnemyStruct& enemy, Point& point)
{

	//“G‚ª¶‚«‚Ä‚¢‚éŽž
	if (enemy.HP > 0)
	{
		if (enemy.Flag)
		{
			enemy.Time++;
			if (enemy.Time >= 20)
			{
				enemy.S++;
				if (enemy.S == 3)enemy.S = 0;

				enemy.Time = 0;
			}

			

			DrawGraph(enemy.SkyEnemyX + ScrollX, enemy.SkyEnemyY, enemy.SkyHandle[enemy.S], true);

			enemy.SkyEnemyX += enemy.PX;
			enemy.SkyEnemyY += enemy.PY;

			//“G‚Æ‚Ì“–‚½‚è”»’è
			//enemy.m_colRect.Draw(GetColor(255, 0, 0), false);
		}
		
	}
	//“G‚ªŽ€‚ñ‚¾Žž
	else if (enemy.HP <= 0)
	{
		if (enemy.SkyEnemyDead == false)
		{
			enemy.m_colRect.SetCenter(0, 0, 0, 0);

			if (enemy.SkyShotDead == true)
			{
				point.SenemyPoint += 50;
				
				enemy.SkyShotDead = false;
			}
			enemy.SkyEnemyflag = false;

			enemy.HP = 1;

			enemy.SkyEnemyX = -640.0f;
			enemy.SkyEnemyY = -20.0f;

			enemy.SkyEnemyDead = true;
		}
	}
}
