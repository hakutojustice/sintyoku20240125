#include "SceneMain.h"
#include"DxLib.h"
#include"Game.h"
#include"Object.h"
#include"Player.h"
#include"Map.h"
#include"Boss.h"
#include"EnemyBase.h"
#include"EnemyToPlayerDir.h"
#include"EneShot.h"
#include"Shot.h"
#include"Laser.h"
#include"CircleShot.h"
#include"ImageGroundManager.h"
#include"Pad.h"

SceneMain::SceneMain()
{
	for (auto& shot : m_pShot)
	{
		shot = nullptr;
	}
	
	for (auto& shot : m_circleShot)
	{
		shot = nullptr;
	}
	for (auto& shot : m_eneShot)
	{
		shot = nullptr;
	}
	m_pPlayer = new Player{this};
	m_pMap = new Map{m_pPlayer};
	m_pBgManager = new ImageGroundManager;
	m_pBoss = new Boss;
	m_pEnemy = new EnemyBase;
	m_pEnemyToPlayer = new EnemyToPlayerDir;
	m_pLaser = nullptr;
}

SceneMain::~SceneMain()
{
	for (auto& shot : m_pShot)
	{
		delete shot;
	}

	for (auto& shot : m_circleShot)
	{
		delete shot;
	}
	for (auto& shot : m_eneShot)
	{
		delete shot;
	}
	delete m_pPlayer ;
	delete m_pMap ;
	delete m_pBgManager ;
	delete m_pEnemy ;
	delete m_pEnemyToPlayer;
	delete m_pLaser;
}

void SceneMain::Init()
{
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);
	m_pBgManager->Init();
	m_pEnemy->Init();
	m_pPlayer->Init();
	m_pMap->Init();
	m_pBoss->Init();
	m_pBoss->GetSceneMain(this);
	m_pEnemy->GetSceneMain(this);
	m_pEnemy->WantPlayerPoint(m_pPlayer);
	m_pEnemyToPlayer->GetSceneMain(this);
	m_pEnemyToPlayer->Init();
}

void SceneMain::End()
{
}



void SceneMain::Update()
{
	CollisionUpdate();

	m_wipeFrame++;

	m_pBgManager->Update();
	m_pPlayer->Update();
	m_pPlayer->GetPos(m_pPlayer->GetVelocity().x);
	/*if (m_pPlayer->GetPos().x > (Game::kScreenWidth * 0.675))
	{
		m_pMap->OnScreenMoveAdd();
		m_pPlayer->screenAdd();	
	}*/
	/*if (m_pPlayer->GetPos().x < (Game::kScreenWidth * 0.375))
	{
		m_pMap->OnScreenMoveSub();
		if (m_pMap->GetScreenMove() <= 0)
		{
			m_pPlayer->screenSub();
		}
	}*/

	m_pMap->OnScreenMoveAdd(m_pPlayer->GetVelocity().x);
	m_pMap->Update();


	if (m_pPlayer->GetPos().x > Game::kScreenWidth*6/8)
	{
		m_pMap->GetScreenMove(3);
	}
	
	if (!bossZone)
	{
		if (m_pMap->GetScreenMove()+m_pPlayer->GetPos().x > 6500)
		{
			screenMove = m_pMap->GetScreenMove();
			m_pMap->GetScreenMove(6750);
			m_pPlayer->GetPos(500);
			bossZone = true;
			m_isClear = true;
		}
	}

	if (m_pEnemyToPlayer != nullptr)
	{
		//for (int e = 0; e < ENEMY_NUM; e++)
		{
			m_pEnemyToPlayer->Update();
		}
	}
	if (m_pEnemy != nullptr)
	{
		//m_pEnemy->GetScreenMove(m_pPlayer->GetVelocity().x);
		m_pEnemy->ScreenMove(m_pMap->GetScreenMove());
		m_pEnemy->Update();

		if (m_pEnemy->OnDie())m_pEnemy = nullptr;
	}
	
	if (m_pBoss != nullptr)
	{
		//m_pBoss->GetScreenMove(m_pPlayer->GetVelocity().x);
		m_pBoss->Update();
		if (m_pBoss->OnDie())m_pBoss = nullptr;
	}

	Pad::Update();
	
	
}

void SceneMain::CollisionUpdate()
{
	//ToDoオブジェクトそれぞれのRectを配列でとってfor文のiで管理する



	//toEnemyのCollision
	if (m_pEnemy != nullptr)
	{
		for (int i = 0; i < SHOT_NUM_LIMIT; i++)
		{
			if (m_pShot[i] != nullptr)
			{
				//for(int e=0;e<8;e++)
				{
					if (m_pShot[i]->GetShotColli(m_pEnemy->GetCollRect()))
					{
						m_pEnemy->OnHitShot();
					}
					if (m_pShot[i]->GetIsDestroy() == true)
					{
						m_pShot[i] = nullptr;
					}
				}
				
			}

		}
	
		for (int i = 0; i < 3; i++)
		{
			if (m_circleShot[i] != nullptr)
			{
				//for (int e = 0; e < 8; e++)
				{

					if (m_circleShot[i]->GetShotColli(m_pEnemy->GetCollRect()))
					{
						m_pEnemy->OnHitShot();
					}
					if (m_circleShot[i]->GetIsDestroy() == true)
					{
						m_circleShot[i] = nullptr;
					}
				}
			}

		}
	
		if (m_pLaser != nullptr)
		{
			//for (int e = 0; e < 8; e++)
			{

				if (m_pLaser->OnLaserCollision(m_pEnemy->GetCollRect()))
				{
					int d = 0;
				}
			}
			if (m_pLaser->GetIsDestroy())
			{
				m_pLaser = nullptr;
			}
		}
		//for (int e = 0; e < 8; e++)
		{

			if (m_pPlayer->OnCollision(m_pEnemy->GetCollRect()))
			{
				//プレイヤーが敵にヒット
				int b = 0;
			}
		}
	}

	//toPlayerのCollision
	if (m_pPlayer != nullptr)
	{
		for (int i = 0; i < 10; i++)
		{
			if (m_eneShot[i] != nullptr)
			{
				if (m_eneShot[i]->GetShotColli(m_pPlayer->GetRect()))
				{
					//Playerが攻撃を受けた処理	
					m_pPlayer->OnDamage();

				}
				if (m_eneShot[i]->GetIsDestroy() == false)
				{
					m_eneShot[i] = nullptr;
				}
			}

		}

		if (m_pMap->IsPlayerCollision(m_pPlayer->GetRect(), m_pPlayer->GetColRadius(), m_pPlayer->GetVelocity()) == true)
		{
			m_pPlayer->OnMapCollision();
		}
		for (int i = 0; i < SHOT_NUM_LIMIT; i++)
		{
			if (m_pShot[i] != nullptr)
			{
				m_pShot[i]->GetScreenMove(m_pPlayer->GetVelocity().x);

				if (!m_pMap->IsCollision(m_pShot[i]->GetPos(), m_pShot[i]->GetRadius()))
				{
					m_pShot[i]->OnMapCol();
				}
				if (m_pShot[i]->GetIsDestroy() == true)
				{
					m_pShot[i] = nullptr;
				}
			}
		}
		if (m_pEnemyToPlayer != nullptr)
		{
			//for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (m_pEnemyToPlayer != nullptr)
				{
					if (m_pMap->IsPlayerCollision(m_pEnemyToPlayer->GetCollRect(), 20, m_pEnemyToPlayer->GetVelocity()))
					{
						m_pEnemyToPlayer->OnMapCol();
					}
				}
			}
		}
	}


}

void SceneMain::Draw() const
{

	//ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;
	
	if (m_shakeFrame > 0)
	{
		//画面揺れ
		screenX = GetRand(8) - 4;
		screenY = GetRand(8) - 4;
	}

	//m_wipeFrameから描画する範囲を計算する
	//m_wipeFrameゲーム開始時に0,
	//毎フレーム加算されてkWipeFrame(30)まで変化する
	//wipeRateはm_wipeFrameの変化に合わせて0.0->1.0に変化する
	float wipeRate = static_cast<float>(m_wipeFrame) / static_cast<float>(30);
	int wipeHeight = Game::kScreenHeight * wipeRate;

	/*DrawRectGraph(screenX,screenY,
		0,0,Game::kScreenWidth, wipeHeight,
		m_gameScreenHandle, true, false);*/

		//offsetの値をwipeの進行に合わせて320->0に変化させたい

		//0->320に変化させるのはわかりやすい  320*wipeRate

	int offset = 320 * (1.0f - wipeRate);

	//画面の上から1ラインずつ描画を行っている
	for (int y = 0; y < Game::kScreenHeight; y++)
	{
		int x = sinf(y * 0.05f) * offset;
		DrawRectGraph(x, y,
			0, y, Game::kScreenWidth, 1,
			m_gameScreenHandle, true, false);
	}
	m_pBgManager->Draw();
	m_pPlayer->Draw();
	//for (int e = 0; e < 8; e++)
	{

		if (m_pEnemy != nullptr)m_pEnemy->Draw();
	}
	if (m_pBoss != nullptr)m_pBoss->Draw();
	if(m_pEnemyToPlayer!=nullptr)
	{
		//for (int e = 0; e < ENEMY_NUM; e++)
		{
			m_pEnemyToPlayer->Draw();
		}
	}
	
	m_pMap->Draw();
	
	
	
	
	
}

void SceneMain::AddShot(std::shared_ptr<Shot> shot)
{
	for (int i = 0; i < SHOT_NUM_LIMIT; i++)
	{
		if(m_pShot[i]==nullptr)
		{
			m_pShot[i] = shot.get();
			break;
		}
		
	}
}

void SceneMain::AddLaser(std::shared_ptr<Laser> laser)
{
	if (m_pLaser == nullptr)
	{
		m_pLaser = laser.get();
		
	}
	
}

void SceneMain::AddCircleShot(std::shared_ptr<CircleShot> circleShot)
{
	for (int i = 0; i < 3; i++)
	{
		if (m_circleShot[i] == nullptr)
		{
			m_circleShot[i] = circleShot.get();
			break;
		}

	}
}

void SceneMain::AddEneShot(std::shared_ptr<EneShot> eneShot)
{
	for (int i = 0; i < 9; i++)
	{
		if (m_eneShot[i] == nullptr)
		{
			m_eneShot[i] = eneShot.get();
			break;
		}

	}
}
