#pragma once
#include "Shot.h"
#include"CollisionMaster.h"


class CircleShot :
    public Shot
{
public:
	CircleShot();
	virtual ~CircleShot();

	void Init();
	virtual void Update();
	void Draw();


	//Shot�̃v���O���~���O����
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec,const int& graph);

	bool GetIsDestroy()const { return m_isVisible; }

	bool GetShotColli(const Rect& rect);

	void setShotBullet() { m_isVisible = false; }

	float GetPosX() { return m_shotPos.x; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shot�̈ʒu���
	Vec2 m_shotPos;
	//Shot�̃x�N�g��
	Vec2 m_Velocity;
	//�x�N�g���̌���
	Vec2 m_DirVec;

	Vec2 m_rotateCenter;

	Vec2 rotatePos;

	Vec2 rotatePos2;
	//Shot�̃O���t�B�b�N�n���h��
	int m_handle;
	int m_graph;

	Sqhere m_collider;

	int m_radius;

	bool m_isVisible = true;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;
	CollisionMaster* m_collosionMaster;

	std::shared_ptr<ShotEffect> m_effect;
};

