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
	maped.Block = LoadGraph("date/ブロック.png");
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
	//マップが端についた時
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

	//描画するマップチップの数をセット
	DrawMapChipNumX = STAGE_WIDTH / MAPCHIP_WIDTH;
	DrawMapChipNumY = STAGE_HEIGHT / MAPCHIP_HEIGHT;

	//画面左上に描画するマップ座標をセット
	MapDrawPointX = player.PlayerX - (DrawMapChipNumX / 2 - 1);
	MapDrawPointY = player.PlayerY - (DrawMapChipNumY / 2 - 1);

	//マップを描く
	for (i = 0; i < DrawMapChipNumY; i++)
	{
		for (j = 0; j < DrawMapChipNumX; j++)
		{

			//マップデータが１だったらブロックを描画する
			if (g_MapChipFirst[i][j] == 1)
			{
				DrawGraph(j * MAPCHIP_WIDTH + ScrollX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

				//当たり判定の更新
				m_colRect.SetCenter(j * MAPCHIP_WIDTH + 10 + ScrollX,i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH,MAPCHIP_HEIGHT);

				//マップチップの当たり判定の表示
				//m_colRect.Draw(GetColor(255, 255, 255), false);
				

				//shotの当たり判定false
				if (m_colRect.IsCollision(shot.m_colRect) == false)
				{
					//shotが壁に当たってない時
				}
				else if (m_colRect.IsCollision(shot.m_colRect) == true)
				{
					//shotが壁に当たった時弾の存在を消す
					shot.Flag = 0;

					DeleteGraph(shot.Graph);
				}

				if (m_colRect.IsCollision(player.m_colRect) == true)
				{
					//ブロックに当たっていたら壁を上る
					player.PlayerY -= 0.15f;

					//ブロックに当たっている判定
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
						//ブロックに当たっていたら壁を上る
						Wenemy[g].WalkEnemyY -= 0.04f;
					}
				}
				for (int s = 0; s < SKY_ENEMY_NOW; s++)
				{
					if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
					{
						//空の敵がブロックにあたっていたら死ぬ
						Senemy[s].HP--;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						Denemy[d].DistanceEnemyY -= 0.04f;
					}
				}
				//敵のショットあたり判定
				for (int e = 0; e < EnemyShotSize; e++)
				{
					if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						enemyShot[e].Flag = 0;

						DeleteGraph(enemyShot[e].Graph);
					}
				}
				
				
				
			}
			//左降りの判定
			if (g_MapChipFirst[i][j] == 2)
			{
				//当たり判定の更新
				m_colBlockRect2.SetCenter(j * MAPCHIP_WIDTH - 5 + ScrollX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

				//マップチップの当たり判定の表示
				//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

				if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
				{
					if (player.PlayerRise == false)
					{
						//プレイヤーを落とす
						player.PlayerY += 0.1f;
					}
					
				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//エネミーを落とす
						Wenemy[g].WalkEnemyY += 0.05f;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
					{
						//エネミーを落とす
						Denemy[d].DistanceEnemyY += 0.05f;
					}
				}
			}
			//右降りの判定
			if (g_MapChipFirst[i][j] == 3)
			{
				//当たり判定の更新
				m_colBlockRect3.SetCenter(j * MAPCHIP_WIDTH + 25 + ScrollX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

				//マップチップの当たり判定の表示
				//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

				if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
				{
					if (player.PlayerRise == false)
					{
						//プレイヤーを落とす
						player.PlayerY += 0.1f;
					}

				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//エネミーを落とす
						Wenemy[g].WalkEnemyY += 0.05f;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
					{
						//エネミーを落とす
						Denemy[d].DistanceEnemyY += 0.05f;
					}
				}
			}
			//2マス分降りるとき
			if (g_MapChipFirst[i][j] == 5)
			{
				//当たり判定の更新
				m_colBlockRect3.SetCenter(j * MAPCHIP_WIDTH + ScrollX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

				//マップチップの当たり判定の表示
				//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

				if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
				{
					if (player.PlayerRise == false)
					{
						//プレイヤーを落とす
						player.PlayerY += 0.1f;
					}

				}

				for (int g = 0; g < ENEMY_NOW; g++)
				{
					if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
					{
						//エネミーを落とす
						Wenemy[g].WalkEnemyY += 0.05f;
					}
				}
				for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
				{
					if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
					{
						//エネミーを落とす
						Denemy[d].DistanceEnemyY += 0.05f;
					}
				}
			}

			//MapFiveのX
			MapFiveX = j * MAPCHIP_WIDTH + ScrollX + MapDistanceFive;
			//MapFourのX
			MapFourX = j * MAPCHIP_WIDTH + ScrollX + MapDistanceFour;
			//MapSixのX
			MapSixX = j * MAPCHIP_WIDTH + ScrollX + MapDistanceSix;

			//↓はランダム配置のマップ形成
			//FiveMasuが0だった場合
			if (FiveMasu == 0)
			{
				

				if (g_MapChip_1[i][j] == 1)
				{
					DrawGraph(MapFiveX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapFiveX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(0, 255, 255), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_1[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapFiveX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_1[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFiveX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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
			
			//FiveMasuが1だった場合
			if (FiveMasu == 1)
			{
				if (g_MapChip_4[i][j] == 1)
				{
					DrawGraph(MapFiveX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapFiveX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(0, 255, 255), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_4[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapFiveX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_4[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFiveX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2マス分降りるとき
				if (g_MapChip_4[i][j] == 5)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFiveX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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
			//FiveMasuが2だった場合
			if (FiveMasu == 2)
			{
				if (g_MapChip_8[i][j] == 1)
				{
					DrawGraph(MapFiveX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapFiveX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(0, 255, 255), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_8[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapFiveX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_8[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFiveX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//1マス分の降りる判定
				if (g_MapChip_8[i][j] == 4)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFiveX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 15, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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


			//FourMasuが0だった場合
			if (FourMasu == 0)
			{
				if (g_MapChip_2[i][j] == 1)
				{
					DrawGraph(MapFourX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapFourX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(255, 0, 255), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_2[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapFourX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_2[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFourX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2マス分降りるとき
				if (g_MapChip_2[i][j] == 5)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFourX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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
			//FourMasuが１だった場合
			if (FourMasu == 1)
			{
				if (g_MapChip_5[i][j] == 1)
				{
					DrawGraph(MapFourX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapFourX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(255, 0, 255), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_5[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapFourX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_5[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFourX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//1マス分の降りる判定
				if (g_MapChip_5[i][j] == 4)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFourX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 15, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2マス分降りるとき
				if (g_MapChip_5[i][j] == 5)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapFourX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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


			//SixMasuが0だった場合
			if (SixMasu == 0)
			{
				if (g_MapChip_3[i][j] == 1)
				{
					DrawGraph(MapSixX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapSixX + 10, i* MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(255, 255, 0), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_3[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapSixX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_3[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapSixX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2マス分降りるとき
				if (g_MapChip_3[i][j] == 5)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapSixX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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
			//SixMasuが1だった場合
			if (SixMasu == 1)
			{
				if (g_MapChip_6[i][j] == 1)
				{
					DrawGraph(MapSixX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapSixX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(255, 255, 0), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_6[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapSixX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_6[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapSixX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//2マス分降りるとき
				if (g_MapChip_6[i][j] == 5)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapSixX, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH - 10, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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
			//SixMasuが2だった場合
			if (SixMasu == 2)
			{
				if (g_MapChip_9[i][j] == 1)
				{
					DrawGraph(MapSixX, i * MAPCHIP_HEIGHT + ScrollY, maped.Block, TRUE);

					//当たり判定の更新
					m_colRect.SetCenter(MapSixX + 10, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colRect.Draw(GetColor(255, 255, 0), false);

					//shotの当たり判定false
					if (m_colRect.IsCollision(shot.m_colRect) == false)
					{
						//shotが壁に当たってない時
					}
					else if (m_colRect.IsCollision(shot.m_colRect) == true)
					{
						//shotが壁に当たった時弾の存在を消す
						shot.Flag = 0;

						DeleteGraph(shot.Graph);
					}

					if (m_colRect.IsCollision(player.m_colRect) == true)
					{
						//ブロックに当たっていたら壁を上る
						player.PlayerY -= 0.15f;
						//ブロックに当たっている判定
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
							//ブロックに当たっていたら壁を上る
							Wenemy[g].WalkEnemyY -= 0.04f;
						}
					}
					for (int s = 0; s < SKY_ENEMY_NOW; s++)
					{
						if (m_colRect.IsCollision(Senemy[s].m_colRect) == true)
						{
							//空の敵がブロックにあたっていたら死ぬ
							Senemy[s].HP = -1;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colRect.IsCollision(Denemy[d].m_colRect) == true)
						{
							//ブロックに当たっていたら壁を上る
							Denemy[d].DistanceEnemyY -= 0.04f;
						}
					}
					//敵のショットあたり判定
					for (int e = 0; e < EnemyShotSize; e++)
					{
						if (m_colRect.IsCollision(enemyShot[e].m_colRect) == false)
						{
							//shotが壁に当たってない時
						}
						else if (m_colRect.IsCollision(enemyShot[e].m_colRect) == true)
						{
							//shotが壁に当たった時弾の存在を消す
							enemyShot[e].Flag = 0;

							DeleteGraph(enemyShot[e].Graph);
						}
					}
				}
				//左降りの判定
				if (g_MapChip_9[i][j] == 2)
				{
					//当たり判定の更新
					m_colBlockRect2.SetCenter(MapSixX - 5, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect2.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect2.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect2.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect2.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
							Denemy[d].DistanceEnemyY += 0.05f;
						}
					}
				}
				//右降りの判定
				if (g_MapChip_9[i][j] == 3)
				{
					//当たり判定の更新
					m_colBlockRect3.SetCenter(MapSixX + 25, i * MAPCHIP_HEIGHT + 10, MAPCHIP_WIDTH, MAPCHIP_HEIGHT);

					//マップチップの当たり判定の表示
					//m_colBlockRect3.Draw(GetColor(0, 255, 255), false);

					if (m_colBlockRect3.IsCollision(player.m_colRect) == true)
					{
						if (player.PlayerRise == false)
						{
							//プレイヤーを落とす
							player.PlayerY += 0.1f;
						}

					}

					for (int g = 0; g < ENEMY_NOW; g++)
					{
						if (m_colBlockRect3.IsCollision(Wenemy[g].m_colRect) == true)
						{
							//エネミーを落とす
							Wenemy[g].WalkEnemyY += 0.05f;
						}
					}
					for (int d = 0; d < DISTANCE_ENEMY_NOW; d++)
					{
						if (m_colBlockRect3.IsCollision(Denemy[d].m_colRect) == true)
						{
							//エネミーを落とす
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
