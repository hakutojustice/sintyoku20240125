#pragma once

struct Enemy
{
	int z = 0;			//アニメーション(仮)
	int moveX = 0;		//敵のx座標の初期化
	int y = 699;		//敵のy座標の初期化
	int z2 = 0;			//アニメーション(仮)
	int moveX2 = 0;	//敵2のx座標の初期化
	int y2 = 699;		//敵2のy座標の初期化
	int R;	//敵の描画1
	int R2;	//敵の描画2
	int R3;
	//int R4;
	int z3 = 0;
	int z4 = 0;
	int moveX3 = 0;
	//int moveX4 = 0;
	int y3 = 699;
	//int y4 = 699;
	int Graph;
	int Graph2;
	int Graph3;
	//int Graph4;
	
};
void InitializeEnemy(Enemy& enemy);
void UpdateEnemy(Enemy& enemy);
void DrawEnemy(Enemy& enemy);
void DDrawBox(Enemy& enemy);
void KillPlayer(Enemy& enemy);
void UpdateBox(Enemy& enemy);