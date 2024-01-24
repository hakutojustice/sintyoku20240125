//�G�l�~�[�̃w�b�_�t�@�C��
#pragma once
//�w�b�_�t�@�C���̓ǂݍ���
#include "Vec2.h"
#include "Rect.h"
//�O���N���X�̓ǂݍ���
class SceneMain;

//�v���g�^�C�v�錾
class Enemy
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
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;
	void EmemyMove();

	//�����o�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	//�G�̂̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }
	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() { return m_colRect; }

	void OnDamage();

	void OnFloor(Rect FloorRect);

	void OnPlayer(Rect PlayerRect);

	//�G�L�����N�^�[���X�^�[�g������

private:
	SceneMain* m_pMain;

	int m_handle;//�O���t�B�b�N�̃n���h��
	int Time;

	//�\���ʒu
	Vec2 m_pos;
	Vec2 m_MoveDir;
	Vec2 m_Move;
	//�����蔻��p�̋�`
	Rect m_colRect;
	Rect m_Rect;

	//�����Ă������
	Dir m_dir;
	int Reverse = false;


	//�����A�j���[�V����
	int m_walkAnimeFrame;
	int i;
	

	bool m_isExist;//���݂��Ă��邩�ǂ����̃t���O(�g�p�����ǂ���)
	bool m_isPrevEnemyFlag;

};

