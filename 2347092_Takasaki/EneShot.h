#pragma once
#include "Shot.h"

class EneShotEffect;

class EneShot 
{
public:
	EneShot();
	virtual ~EneShot();

	void Init();
	virtual void Update();
	void Draw();


	//Shot�̃v���O���~���O����
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph, std::shared_ptr<EneShotEffect> eneShotEffect);

	bool GetIsDestroy()const { return m_isVisible; }

	bool GetShotColli(const Rect& rect);

	void setShotBullet() { m_isVisible = false; }

	void OnDestroy() { m_isDestroy = true; m_shotEffect = nullptr; }

	float GetPosX() { return m_shotPos.x; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shot�̈ʒu���
	Vec2 m_shotPos;
	//Shot�̃x�N�g��
	Vec2 m_Velocity;
	//�x�N�g���̌���
	Vec2 m_DirVec;
	//Shot�̃O���t�B�b�N�n���h��
	int m_handle;
	int m_graph;

	Sqhere m_collider;

	int m_radius;

	bool m_isVisible = true;

	bool m_isEffectFlag = false;

	bool m_isDestroy=false;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;

	std::shared_ptr<EneShotEffect> m_shotEffect;
};

