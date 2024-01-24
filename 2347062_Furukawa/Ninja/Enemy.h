#pragma once
#include "Rect.h"
#include <memory>

class Map;
class Enemy 
{
public:
	Enemy();
	virtual ~Enemy() {}
	void Update();
	void Draw();


	//プレイヤーの足元中央を基準とした座標
	float m_x;
	float m_y;

	//プレイヤーの加速度	1フレーム当たりの移動量
	float m_moveX;
	float m_moveY;


};

