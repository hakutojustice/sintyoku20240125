//�v���C��ʂ̃w�b�_�t�@�C��
#pragma once
//�O���̃N���X�̌Ăяo��
class Player;
class Floor;
class Enemy;
class SceneMain;
//�v���g�^�C�v�錾
class Gamepart
{
public:
	Gamepart();
	~Gamepart();

	void Init();
	void Update();
	void Draw();

private:
	//�O���t�B�b�N�̃n���h��
	int m_GamePlayerHandle;
	int m_enemyHandle;
	int m_bgHandle;
	int m_wallHandle;

	bool m_isEnemyhit = false;
	bool m_isGoal = false;
	//�v���C���[
	Player* m_pPlayer;

	//��
	Floor* m_pFloor;

	//�G�l�~�[
	Enemy* m_pEnemy;
};

