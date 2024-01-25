#pragma once
#include<iostream>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"

namespace
{
	constexpr int SHOT_NUM_LIMIT = 100;
};



class SceneMain;
class Shot;
class ShotEffect;
class Laser;
class CircleShot;



class Player : public Object
{
	
public:
	//using Shot = std::shared_ptr<Shot>;

	Player(SceneMain* main);
	~Player();

	void Init();
	void PlayerMove();
	void ShotIt();
	void DeleteShot();
	void Update();
	void Draw();
	void VelocityToZero();
	void OnDamage();

	void OnMapCollision();
	bool OnCollision(Rect rect);

	int GetColRadius() const{ return m_collisionRadius; }

	Vec2 GetVelocity()const { return m_velocity; }
	
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetPos(int move) { m_pos.x -= move; return m_pos; }

	Rect& GetRect() { return m_playerCol; }

	void screenAdd() { m_isScreenAdd = true; }
	void screenSub() { m_isScreenSub = true; }



private:
	/*�����o�ϐ�*/
	//Pos
	Vec2 m_pos;//���W
	Vec2 m_size;//�T�C�Y
	Vec2 m_velocity;//���x
	Vec2 m_dir;//����
	Vec2 m_animFrame;//�A�j���[�V�����t���[��
	Rect m_playerCol;
	//�U��
	Vec2 m_fireDir;//�Ə��̕���
	Vec2 m_bulletStartPos;//�e�̐����ʒu
	//�t���O
	bool m_isGroundFlag;//�n�ʂƐڐG���Ă���
	bool m_isJumpFlag;//�W�����v����ǂݎ��Flag
	bool m_isDushFlag;//�_�b�V�����Ă��邩
	bool m_isFaceDownFlag;//����
	bool m_isLeftFlag;//���������Ă邩�t���O



	bool flyFlag;

	Vec2 flySpeed;//��s�����x

	int flyingFrame;

	int m_collisionRadius;//���͈̔͂̒��ł��������蔻������Ȃ�
	
	int m_handle;//�v���C���[��graphHandle;
	
	int m_ShotGraph;//�e�̃O���t�B�b�N�n���h��

	int m_kindOfBullet;

	int m_Hp;

	float m_angle;
	float m_rotateAngle;

	float toZeroSpeed;

	bool m_isScreenAdd;
	bool m_isScreenSub;


/////////////////////////////////	
	

//////////*Shot�֘A*///////////
	//Shot* m_shot[SHOT_NUM_LIMIT];
	//Shot m_shot[SHOT_NUM_LIMIT];
	std::shared_ptr<Shot> m_shot[SHOT_NUM_LIMIT] ;

	std::shared_ptr<ShotEffect> m_shotEffect[SHOT_NUM_LIMIT];
	std::shared_ptr<Laser> m_laser;
	std::shared_ptr<CircleShot> m_circleShot[3];


	//�e�̔��˃t���O
	bool shotBulletFlag;

	int m_shotBulletInterval = 20;

///////////////////////////////
	


///////////*���̑�*////////////

	SceneMain* m_WorldMana;

///////////////////////////////

};

