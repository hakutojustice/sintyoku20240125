#pragma once

#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"

class Shot
{
public:
	int ShotX;
	int ShotY;
	int ShotW;
	int ShotH;
	int ShotFlag;
	int ShotGraph;


	void Inti();
	void Update(Player& player, Enemy& enemy);
	void Draw();
};