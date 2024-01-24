//�v���C���[�̃w�b�_�t�@�C��
#pragma once
//�w�b�_�t�@�C���̓ǂݍ���
#include "Vec2.h"
#include "Rect.h"
//�O���N���X�̓ǂݍ���
class SceneMain;
//�v���g�^�C�v�錾
class Player
{
public:
	//�����Ă������
	enum Dir
	{
		kDirDown,	//��
		kDirLeft,	//��
		kDirRight,	//�E
		kDirUp		//��
	};

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw() const;
	void PlayerMove();

	//�����o�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	//�v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() { return m_colRect; }

	bool GetGoalFlag () const { return m_isGoal; }

	void OnDamage();

	void OnFloor(Rect FloorRect);

	void OnEnemy(Rect EnemyRect);

private:
	SceneMain* m_pMain;
	
	int m_handle; //�O���t�B�b�N�̃n���h��

	//�\���ʒu
	Vec2 m_pos;
	Vec2 m_Jump;
	Vec2 m_MoveDir;
	Vec2 m_Move;
	//�����蔻��p�̋�`
	Rect m_colRect;

	//�����Ă������
	Dir m_dir;
	//�����A�j���[�V����
	int m_walkAnimeFrame;
	
	//�_���[�W�󂯂Ă���̃t���[����
	//���i��0
	//�����������Ƀt���[������ݒ肵��
	//�ȍ~���t���[�����炵�Ă���
	int m_damageFrame;

	//�W�����v�̏���
	int JumpPower;
	bool JumpFlag = false;
	bool LastHitKey = false;
	int Jump;

	//��q������Ă��鎞�̏���
	bool m_isladderClimbFlag = false;

	//����o���Ă��鎞�̏���
	bool m_isToFloorFlag = false;

	//
	int y_prev;
	int y_temp;

	//���Ԃ̏���
	int Time;
	int num;
	int i;

	//���]�̏���
	bool Reverse = false;
	//�G�ɂ����������ꍇ�̃t���O
	bool m_isEnemyhit = false;
	//�S�[���ɂ��ǂ蒅�������̏���
	bool m_isGoal = false;

};

