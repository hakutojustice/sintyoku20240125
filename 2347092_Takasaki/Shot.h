#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"
#include"Sqhere.h"

class Player;
class EnemyBase;
class ShotEffect;


class Shot : public Object
{
public:
	Shot();
	virtual ~Shot();

	void Init();
	virtual void Update();
	void Draw();


	//Shot�̃v���O���~���O����
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph, std::shared_ptr<ShotEffect> shotEffect);

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli(const Rect& rect);


	void setShotBullet() { m_isVisible = false; }

	Vec2 GetPos() { return m_shotPos; }

	void GetScreenMove(int screenmove) { m_screenMove = screenmove; }

	void OnDestroy() { m_isDestroy = true; m_shotEffect = nullptr; }

	void OnMapCol();

	int GetRadius() { return m_radius; }

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

	int m_screenMove;

	bool m_isVisible = true;

	bool m_isDestroy = false;

	bool effectFlag=false;

	bool m_isMapColFlag=false;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;

	std::shared_ptr<ShotEffect> m_shotEffect;
};
