#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"
#include"Sqhere.h"

class Player;

class Missile
{
public:
	Missile();
	~Missile();
	void Init();
	virtual void Update();
	void Draw();


	//Shot�̃v���O���~���O����
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph,Player* player);

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli(const Rect& rect);


	void setShotBullet() { m_isVisible = false; }

	Vec2 GetPos() { return m_shotPos; }

	void OnDestroy() { m_isDestroy = true; }

	void OnMapCol();

	int GetRadius() { return m_radius; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shot�̈ʒu���
	Vec2 m_shotPos;

	Vec2 m_missileEndPos;

	Vec2 m_targetPos;
	//Shot�̃x�N�g��
	Vec2 m_Velocity;
	//�x�N�g���̌���
	Vec2 m_DirVec;
	//Shot�̃O���t�B�b�N�n���h��
	int m_handle;
	int m_graph;

	Sqhere m_collider;

	int m_radius;

	int m_lockOnFrame=0;

	bool m_isVisible = true;

	bool m_isDestroy = false;

	bool effectFlag = false;

	bool m_isMapColFlag = false;

	Vec2 m_graphSize;

	Player* m_player;
	
};

