#include "Map.h"
#include "DxLib.h"

Map::Map():
	ScrollX(0),
	ScrollY(0),
	i(0),
	j(0),
	MapDrawPointX(0),
	MapDrawPointY(0),
	DrawMapChipNumX(0),
	DrawMapChipNumY(0),
	DrawW(0),
	DrawH(0),
	DrawMapGraph(0),
	FiveMasu(-1),
	FourMasu(-1),
	SixMasu(-1),
	Five(false),
	Four(true),
	Six(true),
	MapDistanceFive(0),
	MapDistanceFour(0),
	MapDistanceSix(0),
	MapSelection(true),
	MapSeparator(637),
	maped(),
	MapFiveX(0),
	MapFourX(0),
	MapSixX(0),
	MapReset(1277),
	FiveCount(0),
	FourCount(0),
	SixCount(0)
{
}

Map::~Map()
{
}

void Map::InitMap()
{
	maped.Block = LoadGraph("date/�u���b�N.png");
	ScrollX = 0;
	ScrollY = 0;
	i = 0;
	j = 0;
	MapDrawPointX = 0;
	MapDrawPointY = 0;
	DrawMapChipNumX = 0;
	DrawMapChipNumY = 0;
	DrawW = 0;
	DrawH = 0;
	DrawMapGraph = 0;
	FiveMasu = -1;
	FourMasu = -1;
	SixMasu = -1;
	Five = false;
	Four = true;
	Six = true;
	MapDistanceFive = 0;
	MapDistanceFour = 0;
	MapDistanceSix = 0;
	MapSelection = true;
	MapSeparator = 637;
	maped;
	MapFiveX = 0;
	MapFourX = 0;
	MapSixX = 0;
	MapReset = 1277;
	FiveCount = 0;
	FourCount = 0;
	SixCount = 0;
}

void Map::UpdateMap(int ScrollX)
{
	if (Five == false)
	{
		FiveMasu = GetRand(2);

		MapDistanceFive = 640 - ScrollX;
	}
	if (Four == false)
	{
		FourMasu = GetRand(1);

		MapDistanceFour = 640 - ScrollX;
	}
	if (Six == false)
	{
		SixMasu = GetRand(2);

		MapDistanceSix = 640 - ScrollX;
	}
	//�}�b�v���[�ɂ�����
	if (MapSeparator + ScrollX <= 0)
	{
		if (MapReset + ScrollX <= 0)
		{
			if (FiveCount > 0)
			{
				FiveMasu = -1;
				FiveCount = 0;
			}
			if (FourCount > 0)
			{
				FourMasu = -1;
				FourCount = 0;
			}
			if (SixCount > 0)
			{
				SixMasu = -1;
				SixCount = 0;
			}
			MapReset += 640;
		}

		MapSelection = false;

		MapSeparator += 640;
		
	}
}

void Map::DrawMap(int ScrollX, Shot& shot,Player& player,WalkEnemyStruct Wenemy[],SkyEnemyStruct Senemy[],DistanceEnemyStruct Denemy[],EnemyShot enemyShot[], int EnemyShotSize)
{

	//�`�悷��}�b�v�`�b�v�̐����Z�b�g
	DrawMapChipNumX = STAGE_WIDTH / MAPCHIP_WIDTH;
	DrawMapChipNumY = STAGE_HEIGHT / MAPCHIP_HEIGHT;

	//��ʍ���ɕ`�悷��}�b�v���W���Z�b�g
	MapDrawPointX = player.PlayerX - (DrawMapChipNumX / 2 - 1);
	MapDrawPointY = player.PlayerY - (DrawMapChipNumY / 2 - 1);

	//�}�b�v��`��
	for (i = 0; i < DrawMapChipNumY; i++)
	{
		for (j = 0; j < DrawMapChipNumX; j++)
		{

			//�}�b�v�f�[�^���P��������u���b�N��`�悷��
			if (g_MapChipFirst[i][j] == 1)
			{
				DrawGraph(j * MAPCHIP_WIDTH + ScrollX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

				//�����蔻��̍X�V
				m_colRect.SetCenter(j * MAPCHIP_WIDTH + 10 + ScrollX,i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH,MAPCHIP_HEIGHT);

				//�}�b�v�`�b�v�̓����蔻��̕\��
				//m_colRect.Draw(GetColor(255, 255, 255), false);
				

				//shot�̓����蔻��false
				if (m_colRect.IsCollision(shot.m_colRect) == false)
				{
					//shot���ǂɓ������ĂȂ���
				}
				else if (m_colRect.IsCollision(shot.m_colRect) == true)
				{
					//shot���ǂɓ����������e�̑��݂�����
					shot.Flag = 0;

					DeleteGraph(shot.Graph);
				}

				if (m_colRect.IsCollision(player.m_colRect) == true)
				{
					//�u���b�N�ɓ������Ă�����ǂ����
					player.PlayerY -= 0.15f;

					//�u���b�N�ɓ������Ă��锻��
					player.PlayerRise = true;
				}
				else if (m_colRect.IsCollision(player.m_colRect) == false)
				{
					player.PlayerRise = false;
				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						Wenemy[g].WalkEnemyY -= 0.04f;
					}
				}
				for (int s = 0; s < SKY_ENEMY_NOW; s++)
				{
					if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
					{
						//��̓G���u���b�N�ɂ������Ă����玀��
						Senemy[s].HP--;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						Denemy[d].DistanceEnemyY -= 0.04f;
					}
				}
				//�G�̃V���b�g�����蔻��
				for (int e = 0; e < EnemyShotSize; e++)
				{
					if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						enemyShot[e].Flag = 0;

						DeleteGraph(enemyShot[e].Graph);
					}
				}
				
				
				
			}
			//���~��̔���
			if (g_MapChipFirst[i][j] == 2)
			{
				//�����蔻��̍X�V
				m_colBlockRect2.SetCenter(j * MAPCHIP_WIDTH - 5 + ScrollX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

				//�}�b�v�`�b�v�̓����蔻��̕\��
				//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

				if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
				{
					if (player.PlayerRise == false)
					{
						//�v���C���[�𗎂Ƃ�
						player.PlayerY += 0.1f;
					}
					
				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//�G�l�~�[�𗎂Ƃ�
						Wenemy[g].WalkEnemyY += 0.05f;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
					{
						//�G�l�~�[�𗎂Ƃ�
						Denemy[d].DistanceEnemyY += 0.05f;
					}
				}
			}
			//�E�~��̔���
			if (g_MapChipFirst[i][j] == 3)
			{
				//�����蔻��̍X�V
				m_colBlockRect3.SetCenter(j * MAPCHIP_WIDTH + 25 + ScrollX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

				//�}�b�v�`�b�v�̓����蔻��̕\��
				//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

				if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
				{
					if (player.PlayerRise == false)
					{
						//�v���C���[�𗎂Ƃ�
						player.PlayerY += 0.1f;
					}

				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//�G�l�~�[�𗎂Ƃ�
						Wenemy[g].WalkEnemyY += 0.05f;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
					{
						//�G�l�~�[�𗎂Ƃ�
						Denemy[d].DistanceEnemyY += 0.05f;
					}
				}
			}
			//2�}�X���~���Ƃ�
			if (g_MapChipFirst[i][j] == 5)
			{
				//�����蔻��̍X�V
				m_colBlockRect3.SetCenter(j * MAPCHIP_WIDTH + ScrollX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

				//�}�b�v�`�b�v�̓����蔻��̕\��
				//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

				if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
				{
					if (player.PlayerRise == false)
					{
						//�v���C���[�𗎂Ƃ�
						player.PlayerY += 0.1f;
					}

				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//�G�l�~�[�𗎂Ƃ�
						Wenemy[g].WalkEnemyY += 0.05f;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
					{
						//�G�l�~�[�𗎂Ƃ�
						Denemy[d].DistanceEnemyY += 0.05f;
					}
				}
			}

			//MapFive��X
			MapFiveX = j * MAPCHIP_WIDTH + ScrollX + MapDistanceFive;
			//MapFour��X
			MapFourX = j * MAPCHIP_WIDTH + ScrollX + MapDistanceFour;
			//MapSix��X
			MapSixX = j * MAPCHIP_WIDTH + ScrollX + MapDistanceSix;

			//���̓����_���z�u�̃}�b�v�`��
			//FiveMasu��0�������ꍇ
			if (FiveMasu == 0)
			{
				

				if (g_MapChip_1[i][j] == 1)
				{
					DrawGraph(MapFiveX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapFiveX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(0, 255, 255), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_1[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapFiveX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_1[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFiveX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Five = true;
				
				if (MapSelection == false)
				{

					Four = false;

					FiveCount = 1;

				}
				MapSelection = true;
				
			}
			
			//FiveMasu��1�������ꍇ
			if (FiveMasu == 1)
			{
				if (g_MapChip_4[i][j] == 1)
				{
					DrawGraph(MapFiveX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapFiveX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(0, 255, 255), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_4[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapFiveX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_4[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFiveX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2�}�X���~���Ƃ�
				if (g_MapChip_4[i][j] == 5)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFiveX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Five = true;

				if (MapSelection == false)
				{

					Four = false;

					FiveCount = 1;

				}
				MapSelection = true;
				
			}
			//FiveMasu��2�������ꍇ
			if (FiveMasu == 2)
			{
				if (g_MapChip_8[i][j] == 1)
				{
					DrawGraph(MapFiveX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapFiveX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(0, 255, 255), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_8[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapFiveX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_8[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFiveX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//1�}�X���̍~��锻��
				if (g_MapChip_8[i][j] == 4)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFiveX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 15, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Five = true;

				if (MapSelection == false)
				{

					Six = false;

					FiveCount = 1;

				}
				MapSelection = true;
				
			}


			//FourMasu��0�������ꍇ
			if (FourMasu == 0)
			{
				if (g_MapChip_2[i][j] == 1)
				{
					DrawGraph(MapFourX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapFourX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(255, 0, 255), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_2[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapFourX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_2[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFourX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2�}�X���~���Ƃ�
				if (g_MapChip_2[i][j] == 5)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFourX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Four = true;

				if (MapSelection == false)
				{

					Six = false;

					FourCount = 1;

				}
				MapSelection = true;
				
			}
			//FourMasu���P�������ꍇ
			if (FourMasu == 1)
			{
				if (g_MapChip_5[i][j] == 1)
				{
					DrawGraph(MapFourX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapFourX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(255, 0, 255), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_5[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapFourX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_5[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFourX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//1�}�X���̍~��锻��
				if (g_MapChip_5[i][j] == 4)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFourX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 15, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2�}�X���~���Ƃ�
				if (g_MapChip_5[i][j] == 5)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapFourX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Four = true;

				if (MapSelection == false)
				{

					Six = false;

					FourCount = 1;


				}
				MapSelection = true;
				
			}


			//SixMasu��0�������ꍇ
			if (SixMasu == 0)
			{
				if (g_MapChip_3[i][j] == 1)
				{
					DrawGraph(MapSixX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapSixX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(255, 255, 0), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_3[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapSixX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_3[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapSixX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2�}�X���~���Ƃ�
				if (g_MapChip_3[i][j] == 5)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapSixX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Six = true;

				if (MapSelection == false)
				{

					Five = false;

					SixCount = 1;

				}
				MapSelection = true;
				
			}
			//SixMasu��1�������ꍇ
			if (SixMasu == 1)
			{
				if (g_MapChip_6[i][j] == 1)
				{
					DrawGraph(MapSixX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapSixX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(255, 255, 0), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_6[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapSixX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_6[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapSixX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2�}�X���~���Ƃ�
				if (g_MapChip_6[i][j] == 5)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapSixX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Six = true;

				if (MapSelection == false)
				{

					Four = false;

					SixCount = 1;


				}
				MapSelection = true;
				
			}
			//SixMasu��2�������ꍇ
			if (SixMasu == 2)
			{
				if (g_MapChip_9[i][j] == 1)
				{
					DrawGraph(MapSixX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//�����蔻��̍X�V
					m_colRect.SetCenter(MapSixX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colRect.Draw(GetColor(255, 255, 0), false);

					//shot�̓����蔻��false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shot���ǂɓ������ĂȂ���
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shot���ǂɓ����������e�̑��݂�����
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//�u���b�N�ɓ������Ă�����ǂ����
						player.PlayerY -= 0.15f;
						//�u���b�N�ɓ������Ă��锻��
						player.PlayerRise = true;
					}
					else if (m_colRect.IsCollision(player.m_colRect) == false)
					{
						player.PlayerRise = false;
					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colRect.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//��̓G���u���b�N�ɂ������Ă����玀��
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�u���b�N�ɓ������Ă�����ǂ����
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//�G�̃V���b�g�����蔻��
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shot���ǂɓ������ĂȂ���
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shot���ǂɓ����������e�̑��݂�����
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//���~��̔���
				if (g_MapChip_9[i][j] == 2)
				{
					//�����蔻��̍X�V
					m_colBlockRect2.SetCenter(MapSixX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//�E�~��̔���
				if (g_MapChip_9[i][j] == 3)
				{
					//�����蔻��̍X�V
					m_colBlockRect3.SetCenter(MapSixX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//�}�b�v�`�b�v�̓����蔻��̕\��
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//�v���C���[�𗎂Ƃ�
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//�G�l�~�[�𗎂Ƃ�
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				Six = true;

				if (MapSelection == false)
				{

					Five = false;

					SixCount = 1;


				}
				MapSelection = true;
				
			}
			
		}
	}
}
