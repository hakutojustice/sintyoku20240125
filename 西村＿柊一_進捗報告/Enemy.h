#pragma once

class Character;
class Enemy
{
	

public:

	void Draw();
	void KillerRabbit(Character&e_chara);
	void EnemyMove();
	void EnemyWallBumped();
	void EnemyAirCollision(Character&e_chara);
	void InitEnemy();
	

	

	//エネミー初期位置
 	int enemyX=300;
	int	enemyY=368;
	
	//ウサギの位置
	float RabbitX = 300;
	float RabbitY = 310;

	

	//エネミーの移動処理
	int enemy_moveX;
	int enemy_moveY;
 

	

	
	

};

