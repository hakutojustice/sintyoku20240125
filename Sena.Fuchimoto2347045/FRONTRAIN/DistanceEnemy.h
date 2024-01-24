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
	//�e�����˒����ǂ���
	bool Flag = false;
	//x���W
	double X = 0;
	//y���W
	double Y = 0;
	//�O���t�B�b�N�n���h��
	int Graph = -1;
	//�摜�̕��ƍ���
	int Width = 0;
	int Height = 0;
	//�e���W�I�Ɍ������Ă���
	double PX = 0;
	double PY = 0;
	//�e�̃_���[�W
	int ShotDamage = 2;

	//�����蔻��̋�`
	Rect m_colRect;
};

struct DistanceEnemyStruct : public EnemyBase
{
	//�G�̌��ݒn
	float DistanceEnemyX = 0.0f;
	float DistanceEnemyY = 0.0f;
	int DistanceEnemyGraph = -1;

	//�G�̑傫��
	int DistanceEnemyWidth = 20;
	int DistanceEnemyHeight = 20;

	//�G�̃X�s�[�h
	float DistanceEnemySpeed = 0.02f;
	//�G�̎��S����
	bool DistanceEnemyDead = false;
	//�G���e�Ŏ��񂾔���
	bool DistanceShotDead = false;

	//�G���o������t���O
	bool DistanceEnemyflag = false;

	//���ݎ��Ԃ𓾂�
	int Time = 0;
	//�G�̒e���˂܂ł̎���
	int ShotEnemy = 0;
	int ShotDistance = 0;

	//�G�����񂾎��̃A�j���[�V�����t���[��
	int m_DeadAnimFrame;

	//�O�̃t���[���Ō��������ǂ���
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

	//�G�̏o���t���O
	bool DistanceEnemyAppearance = true;

	//���Ԃ�i�߂�ϐ�
	int T = 0;
};

