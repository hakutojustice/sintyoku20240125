#pragma once
#include"Vec2.h"
class ForeGround
{
public:
	ForeGround();
	~ForeGround();

	void Init();
	void Update();
	void Draw();

	// �O���t�B�b�N�̐ݒ�
	void SetHandle(int handle) { m_handle = handle; }
private:
	int m_handle;

	Vec2 m_pos;
};


