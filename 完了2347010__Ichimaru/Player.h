#pragma once
#include "Enemy.h"

struct Player
{
	int PlayerX = 699;
	int PlayerY = 699;
	int JumpPower = 0;
	int PlayerGraph;
	int PlayerGraph2;
	int Key;
	int Score;  // ÉXÉRÉAÇí«â¡
	int IsJumping;
	int BGMHandle;
	int ScoreVisible;
	int Dead = 0;
	
};

void InitializePlayer(Player& player);
void UpdatePlayer(Player& player, Enemy& enemy);
void UpdatePlayer(Player& player);
void DDrawBox(Player& player);
void CheckCollision(Player& player, Enemy& enemy);

