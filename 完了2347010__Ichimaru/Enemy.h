#pragma once

struct Enemy
{
	int z = 0;			//ƒAƒjƒ[ƒVƒ‡ƒ“(‰¼)
	int moveX = 0;		//“G‚ÌxÀ•W‚Ì‰Šú‰»
	int y = 699;		//“G‚ÌyÀ•W‚Ì‰Šú‰»
	int z2 = 0;			//ƒAƒjƒ[ƒVƒ‡ƒ“(‰¼)
	int moveX2 = 0;	//“G2‚ÌxÀ•W‚Ì‰Šú‰»
	int y2 = 699;		//“G2‚ÌyÀ•W‚Ì‰Šú‰»
	int R;	//“G‚Ì•`‰æ1
	int R2;	//“G‚Ì•`‰æ2
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