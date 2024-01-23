#pragma once
#include "EnemyBase.h"

class EnemyToPlayerDir :
    public EnemyBase
{
public:
    EnemyToPlayerDir();
    virtual ~EnemyToPlayerDir();

    virtual void Init() ;
	void CollisionUpdate();
    virtual void Update() override;
    virtual void Draw();

	void WantPlayerPoint(Player* player);

	void OnDamage(int Atk) { m_Hp - Atk; }

	void OnHitShot();

	void OnMapCol();

	bool OnDie();

	Rect& GetCollRect() { return m_colRect; }

	Vec2 GetEnePos() { return m_pos; }

	Vec2 GetVelocity() { return m_velocity; }

	void GetSceneMain(SceneMain* sceneMain) { m_WorldMana = sceneMain; }
private:
    int m_Hp;

    int m_handle;

    int m_attackFrame;
	int m_shotGraph;


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
	EneShot* m_shot;

	//�e�̔��˃t���O
	bool shotBulletFlag;

	///////////////////////////////


	SceneMain* m_WorldMana;

};

