
//��ʕ\���̃w�b�_�t�@�C��
#pragma once
//�w�b�_�t�@�C���ǂݍ���
#include "Vec2.h"
#include<Vector>
//���O��Ԃ̏���
using namespace std;

//�N���X�Ăяo��
	class Gamepart;
	class Bg;
	class EnemyBase;
//�v���g�^�C�v�錾
class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();
	
	void Init();
	void End();

	void Update();
	void Draw() const;

	//����̍��W�����ԋ߂��ɂ���G�̍��W��Ԃ��֐�
	Vec2 GetNearEemyPos(Vec2 pos) const;
	//�M��ǉ�����֐�
	//�o�^�ł��Ȃ������ꍇ��false��Ԃ�
	//�o�^�ł��Ȃ������ꍇ�͓�����pShot�J������

private:
	//�G�L�����N�^�[�̐���
	void CreateEnemyLeft();
	void CreateEnemyRight();
	void CreateEnemyToPlayer();

private:
	//�O���t�B�b�N�̃n���h��
	int m_gameScreenHandle;
	
	int m_GamePartHandle;
	int m_enemyHandle;
	int m_bgHandle;
	int m_wallHandle;

	//�v���C���[
	Gamepart* m_pgamePart ;
	//�w�i
	Bg* m_pBg; 
	//�G

	//�M

	//��ʃ��C�v����
	int m_wipeFrame;

	//�G�̓o��Ԋu

	//��ʂ��h��鉉�o
	int m_shakeFrame;
	
};

