#include "DxLib.h"
#include "Enemy.h"
#include "Haikei.h"
#include "game.h"
#include "key.h"
#include "Player.h"

void InitializeHaikei(Haikei& haikei)
{
	haikei.Graph = LoadGraph("data/Haikei.png");
	haikei.X = 0;
	haikei.Y = 0;
}

void UpdateHaikei(Haikei& haikei)	
{
	DrawGraph(haikei.X, haikei.Y, haikei.Graph, false);
}

void DrawHaikei(Haikei& haikei)
{

}