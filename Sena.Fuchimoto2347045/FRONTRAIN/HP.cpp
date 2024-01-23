#include "HP.h"
#include "Player.h"

void HP::PlayerHP(Player& player)
{
	//プレイヤー真上にHPが表示される
	DrawFormatString(player.PlayerX - 8, player.PlayerY - 30, GetColor(0, 255, 0), "%d",player.HP);
}
