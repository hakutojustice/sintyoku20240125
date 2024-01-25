#pragma once
#include<iostream>
#include<memory>
#include<list>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"



using namespace std;

class Player;
class EneShot;
class SceneMain;
class EneShotEffect;

class EnemyBase
{
public:
	EnemyBase();
	//EnemyBase(Vec2 pos);�}�b�v���w�肵���ʒu�ɓG��a��
	~EnemyBase();

	void Init();
	void CollisionUpdate();
	virtual void Update();
	void Draw();

	void OnDamage(int Atk) { m_Hp - Atk; }

	void OnHitShot();

	void WantPlayerPoint(Player* player);

	void ScreenMove(int screenmove) { m_screenMove=screenmove; };

	void GetScreenMove(float veloX);

	bool OnDie();

	void GetSceneMain(SceneMain* sceneMain) { m_WorldMana = sceneMain; }

	Rect GetCollRect()const { return m_colRect; }

	Vec2 GetEnePos() { return m_pos; }

private:
	int m_Hp;

	int m_handle;

	int m_attackFrame;

	int m_shotGraph;
	
	int m_distance;

	int m_screenMove;

	bool m_isShotCollFlag;

	bool m_isDeathFlag;

	Vec2 m_targetPos;
	Vec2 m_fireDir;//�Ə��̕���

	Vec2 m_pos;
	Vec2 m_graphSize;

	Vec2 m_velocity;

	//�A�j���[�V�����̊Ǘ�
	Vec2 animFrameMana;

	Rect m_colRect;

	
	Player* m_player;

	//////////*Shot�֘A*///////////
	std::shared_ptr<EneShot> m_shot[10];
	std::shared_ptr<EneShotEffect>m_shotEffect[10];
	//�e�̔��˃t���O
	bool shotBulletFlag;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

