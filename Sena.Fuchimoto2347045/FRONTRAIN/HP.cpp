#include "HP.h"
#include "Player.h"

void HP::PlayerHP(Player& player)
{
	//�v���C���[�^���HP���\�������
	DrawFormatString(player.PlayerX - 8, player.PlayerY - 30, GetColor(0, 255, 0), "%d",player.HP);
}
