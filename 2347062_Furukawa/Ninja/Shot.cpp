#include "Shot.h"

void Shot::Inti()
{
	//�e�̃O���t�B�b�N���������Ƀ��[�h
	ShotGraph = LoadGraph("date/Shot.png");

	//�e�̃O���t�B�b�N�T�C�Y������
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//�e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂu���݂��Ă��Ȃ��v���Ӗ�����0�������Ă���
	ShotFlag = 0;
}

void Shot::Update(Player& player, Enemy& enemy)
{
	//���������Ă��āA�e���`�悳��Ă��Ȃ���
	//if (CheckHitKey(KEY_INPUT_LEFT) == 1 && ShotFlag == 0)
	//{
	//	//�v���C���[�ƒe�̉摜�̃T�C�Y�𓾂�
	//	GetGraphSize(player.PlayerGraph, &player.PlayerW, &player.PlayerH);
	//	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//	//�e�̈ʒu���Z�b�g�A�ʒu�̓v���C���[�̒��S�ɂ���
	//	ShotX = (player.PlayerW - ShotW) / 2 + player.PlayerX;
	//	ShotY = (player.PlayerH - ShotH) / 2 + player.PlayerY;

	//	ShotFlag = 1;
	//}

	//�e���`�悵�Ă���Ƃ�
	//if (ShotFlag == 1)
	//{
	//	//�e�ƃG�l�~�[�̓����蔻��
	//	if (((ShotX > enemy.X && ShotY < enemy.X + enemy.W) ||
	//		(enemy.X > ShotX && enemy.X < ShotX + ShotW)) &&
	//		((ShotY > enemy.Y && ShotY < enemy.Y + enemy.H) ||
	//			(enemy.Y > ShotY && enemy.Y < ShotY + ShotH)))
	//	{
	//		//�ڐG���Ă���ꍇ�͓��������G�l�~�[�̑��݂�����
	//		
	//	}
	//}
}

void Shot::Draw()
{
	//�e�̈ړ�
	if (ShotFlag == 1)
	{
		//�e��30�h�b�g��Ɉړ�������
		ShotX += 30;

		//��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ���0(���݂��Ȃ�)��������
		if (ShotX > 1600)
		{
			ShotFlag = 0;
		}
		//��ʂɒe��`�悷��
		DrawGraph(ShotX, ShotY, ShotGraph, false);
	}
}
