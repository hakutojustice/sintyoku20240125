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
	//�G�̃X�s�[�h�ݒ�
	double tb, tbx, tby, px, py, sx, sy;

	//���Ԃ����ƓG���o��
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

					//�G�l�~�[�������_���ȏꏊ�ɏo��
					
					enemy[i].SkyEnemyX = GetRand(640) - ScrollX;

					enemy[i].SkyEnemyY = -10.0f;

					//��̂������̂Ń��[�v���甲����
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
			//�G�������Ă��鎞
			if (enemy[i].HP >= 0)
			{
				if (enemy[i].Flag == false)
				{
					enemy[i].Flag = true;
					//�G�̈ړ�����
					sx = enemy[i].SkyEnemyX + enemy[i].SkyEnemyWidth / 2;
					sy = enemy[i].SkyEnemyY + enemy[i].SkyEnemyHeight / 2;
					px = player.PlayerX - ScrollX + player.PlayerWidth / 2;
					py = player.PlayerY + player.PlayerHeight / 2;

					tbx = px - sx;
					tby = py - sy;

					tb = sqrt(tbx * tbx + tby * tby);

					//1�t���[��������7�h�b�g�œ���
					enemy[i].PX = tbx / tb * 7;
					enemy[i].PY = tby / tb * 7;

					//��̂������̂Ŕ�����
					break;
				}
				
			}

			//�����蔻��̍X�V
			enemy[i].m_colRect.SetCenter(enemy[i].SkyEnemyX + 7 + player.ScrollX, enemy[i].SkyEnemyY + 10, enemy[i].SkyEnemyWidth, enemy[i].SkyEnemyHeight);

			//�v���C���[�̓����蔻��
			if (enemy[i].m_colRect.IsCollision(player.m_colRect) == false)
			{
				//�������ĂȂ�
			}
			//�������Ă���
			else if (enemy[i].m_colRect.IsCollision(player.m_colRect) == true)
			{
				//1�񂾂����s
				if (player.PlayerDamage == false)
				{
					player.HP -= Senemy.Attack;

					player.PlayerDamage = true;
				}
				

				enemy[i].HP = -1;
			}

			if (shot.Flag == 1)
			{
				//�G�Ƃ̓����蔻��
				if (enemy[i].m_colRect.IsCollision(shot.m_colRect) == false)
				{
					//�������ĂȂ�
				}
				else if (enemy[i].m_colRect.IsCollision(shot.m_colRect) == true)
				{
					enemy[i].HP -= shot.Damage;
					//�ڐG���Ă���ꍇ�͓��������e�̑��݂�����
					shot.Flag = 0;

					enemy[i].SkyShotDead = true;

				}
			}
			//���Ƃ̓����蔻��
			if (shield.LeftFlag == true || shield.RightFlag == true)
			{
				//���ƐڐG
				if (enemy[i].m_colRect.IsCollision(shield.m_colRect) == false)
				{
					//�������ĂȂ�
				}
				else if (enemy[i].m_colRect.IsCollision(shield.m_colRect) == true)
				{
					//���ɓ��������玀��
					enemy[i].HP = -1;
				}
			}


		}
	}

}

void SkyEnemy::Draw(float ScrollX, SkyEnemyStruct& enemy, Point& point)
{

	//�G�������Ă��鎞
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

			//�G�Ƃ̓����蔻��
			//enemy.m_colRect.Draw(GetColor(255, 0, 0), false);
		}
		
	}
	//�G�����񂾎�
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
