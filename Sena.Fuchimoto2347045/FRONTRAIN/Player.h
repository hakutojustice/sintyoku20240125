#pragma once
#include "Rect.h"
#include "Map.h"
#include "WalkEnemy.h"
#define SHOT 30

struct Shield
{
	//���̔����t���O
	bool LeftFlag = false;
	bool RightFlag = false;

	//�O���t�B�b�N�n���h��
	int ShieldGraph = -1;

	//���̕��ƍ���
	int ShieldWidth = 0;
	int ShieldHeight = 0;

	//�����蔻��̋�`
	Rect m_colRect;
};

struct Shot
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
	//�e���Ə��Ɍ������Ă���
	double AimX = 0;
	double AimY = 0;
	//�e�̃_���[�W
	int Damage = 3;
	

	//�����蔻��̋�`
	Rect m_colRect;

};

class WalkEnemy;
class Map;

class Player
{
public:
	Player();
	~Player();

	void Init(Shield& shield, Shot shot[]);
	void InitShot(Shot shot[]);
	void Update(Player& player, Map& map, Shield& shield);
	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() { return m_colRect; }

	void ShotUpdate(Player& player, Shot shot[], int shotSize);

	void Draw(Shield& shield, Player& player);
	void DrawShot(Shot& shot);

	//�e
	Shot shot[SHOT];

	//�v���C���[��HP
	int HP;
	//�v���C���[�̏����ʒu
	float PlayerX;
	float PlayerY;
	//�v���C���[�̃T�C�Y
	int PlayerWidth, PlayerHeight;

	//��ʃX�N���[��
	float ScrollX, ScrollY;

	//�X�N���[������
	bool PlayerRight;

	//�_���[�W����
	bool PlayerDamage;

	//�e�؂�ϐ�
	int Bullet = 12;

	//�����[�h����
	int BulletTime = 0;

	//�v���C���[���ǂ�����Ă��锻��
	bool PlayerRise;

	//�_���[�W�J�E���g
	int Count = 0;

	//�d��
	float Gravity = 0.3f;

	//�����蔻��̋�`
	Rect m_colRect;

private:
	
	float Speed;
	//�v���C���[�̉摜������ϐ�
	int playerGraph;

	//�Ə��̉摜������ϐ�
	int Aiming;

	//�Ə��̉摜�T�C�Y
	int AimingW, AimingH;

	//�}�E�X�̍��W�擾
	int MouseX, MouseY;

	//�ړ����锻��
	bool Left;
	bool Right;

	//�v���C���[�̕��ƍ���
	int PlayerW;
	int PlayerH;

	//�O�̃t���[���ŃV���b�g�����������ǂ���
	bool PlayerShotFlag;

	//�e�̉摜�T�C�Y
	int ShotGraph;
	int W, H;

	//�}�b�v�`�b�v���W
	int rightMapX = 0;
	int leftMapX = 0;
	int upMapY = 0;
	int downMapY = 0;

	//�X�N���[������
	int maxDrawMapX; //�ő�̕`��͈�X
	int minDrawMapX = 0;   //�ŏ��̕`��͈�X
	int mapScrollX = 0;   //�X�N���[����X
	int moveNumX = 0;    //���ړ���X
};