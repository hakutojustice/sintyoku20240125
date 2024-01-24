#pragma once
#include "Game.h"
#include"Vec2.h"
#include"Rect.h"
#include <iostream>
#include <vector>
#include <algorithm>

//namespace
//{
//	constexpr int ENEMY_NUM = 30;
//}

class Player;

class Map
{
public:
	Map(Player* player);
	~Map();

	void Init();
	void Update();
	void Draw();

	int GetScreenVelocity() { return screenVelocityX; }

	bool IsPlayerCollision(Rect& rect,int colRadius, Vec2 velo);
	bool IsCollision(Rect& rect, Vec2 velo);
	bool IsCollision(Vec2 pos, int radius);

	

	//Vec2 GetEnePos() { return m_enemyPos; }
	
	int GetScreenMove() { return screenMove; }
	int GetScreenMove(int move) { screenMove = move; return screenMove; }

	void OnScreenMoveAdd(float veloX) { m_isScreenMoveAddFlag = true; screenMove += veloX;}

	


private:
	

	int m_handle;
	int m_graphX;
	int m_graphY;
	int graphRateX;


	// �O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;

	int screenVelocityX;//�X�N���[����x���ړ���(�t���[���P��)
	int screenMove;//�X�N���[����x���ړ���(���v)

	bool m_isScreenMoveAddFlag;
	bool m_isScreenMoveSubFlag;


	Player* m_player;

	Vec2 m_playerPos;

	



	
};

