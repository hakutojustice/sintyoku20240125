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
	//�G�̌��ݒn
	float SkyEnemyX = 0.0f;
	float SkyEnemyY = 0.0f;
	int SkyHandle[3];

	//�A�j���[�V�����摜�\���̕ϐ�
	int S = 0;

	int Time = 0;

	//�G�̑傫��
	int SkyEnemyWidth = 15;
	int SkyEnemyHeight = 10;

	//�G���v���C���[�Ɍ������Ă���
	double PX = 0;
	double PY = 0;

	//�G�����������ǂ���
	bool Flag = false;

	//�G�̎��S����
	bool SkyEnemyDead = false;
	//�G���e�Ŏ��񂾔���
	bool SkyShotDead = false;

	//�G���o������t���O
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

	//�G�̏o���t���O
	bool SkyEnemyAppearance = true;

	

	//���Ԃ�i�߂�ϐ�
	int T = 0;
};

