//���̒�q�̕`�揈��
#pragma once
//�w�b�_�t�@�C���̓ǂݍ���
#include "Vec2.h"
#include "Rect.h"
//�O���̃N���X�̓ǂݍ���
class SceneMain;
//�v���g�^�C�v�錾
class Floor
{
public:
	Floor();
	~Floor();

	void Init();
	void Update();
	void Draw();
	Rect GetRect() const { return m_Rect; }

	//�����o�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

	//�w�肵����`�Ɠ������Ă��邩����
	bool IsCol(Rect rect);

	SceneMain *m_pMain;

	//�O���t�B�b�N�̃n���h��
	int m_handle;

	//�ǂ̕��i
	Vec2 m_Pos;
	Rect m_Rect;

	int m_height;
	int m_width;
	
	bool m_isGoal = false;

	


	int i;


};

