#pragma once

#include "Rect.h"
#include "Enemy.h"
#include <memory>

class Map;
class Enemy;
class Player
{
public:
	Player();
	virtual ~Player() {}


	void Update(Enemy& enemy);
	void Draw();


private:

	//ジャンプ
	float m_isJump;

	//プレイヤーの足元中央を基準とした座標
	float m_x;
	float m_y;

	//プレイヤーの加速度	1フレーム当たりの移動量
	float m_moveX;
	float m_moveY;

	float m_damage;

	float PlayerFlog;

	//プレイヤーの描画
	//float PlayerGraph;
};
