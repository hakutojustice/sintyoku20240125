//ゲームのプレイ画面のソースファイル

//ヘッダファイル読み込み
#include "SceneMain.h"
#include "Gamepart.h"
#include "Player.h"
#include "Floor.h"
#include "Enemy.h"

#include "DxLib.h"
#include <cassert>

//コンストラクタ
Gamepart::Gamepart()
{
	//グラフィックのロード
	m_GamePlayerHandle = LoadGraph("data/Player.png");
	assert(m_GamePlayerHandle != -1);
	m_enemyHandle = LoadGraph("data/Enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/Map.png");
	assert(m_bgHandle != -1);
	m_wallHandle = LoadGraph("data/Wall.png");
	assert(m_wallHandle != -1);


	//床のメモリ確保
	m_pFloor = new Floor;
	m_pFloor->SetHandle(m_wallHandle);
	//プレイヤーのメモリ確保
	m_pPlayer = new Player;
	m_pPlayer->SetHandle(m_GamePlayerHandle);
	//敵のメモリの確保
	m_pEnemy = new Enemy;
	m_pEnemy->SetHandle(m_enemyHandle);
}
//デストラクタ
Gamepart::~Gamepart()
{
	//メモリ削除
	DeleteGraph(m_GamePlayerHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_wallHandle);

	//床とプレイヤーのメモリ開放
	delete m_pFloor;
	delete m_pPlayer;
	m_pFloor = nullptr;
	m_pPlayer = nullptr;
	//エネミーのメモリ開放
	delete m_pEnemy;
	m_pEnemy = nullptr;
}
//初期化処理
void Gamepart::Init()
{
	m_pFloor->Init();
	m_pPlayer->Init();
	m_pEnemy->Init();
}
//更新処理
void Gamepart::Update()
{
	if (m_isEnemyhit == false && m_isGoal == false)
	{
		//Floorの更新処理を読み込む
		m_pFloor->Update();
		//Playerの更新処理を読み込む
		m_pPlayer->Update();
		//Enemyの更新処理を読み込む
		m_pEnemy->Update();
		//当たり判定の読み込み
		Rect playerRect = m_pPlayer->GetColRect();
		Rect floorRect = m_pFloor->GetRect();
		Rect EnemyRect = m_pEnemy->GetColRect();
		//ターゲットの指定
		if (playerRect.IsCollsion(floorRect))
		{
			//m_pPlayer->OnFloor(floorRect);
		}
		//ターゲットの指定
		if (EnemyRect.IsCollsion(playerRect))
		{
			//m_pPlayer->OnEnemy(EnemyRect);
			m_isEnemyhit = true;
		}

		if (m_pPlayer->GetGoalFlag() == true)
		{
			m_isGoal = true;
		}
	}
}
//描画処理
void Gamepart::Draw()
{
	m_pFloor->Draw();
	m_pPlayer->Draw();
	m_pEnemy->Draw();

	Vec2 PlayerPos = m_pPlayer->GetPos();
	Vec2 EnemyPos = m_pEnemy->GetPos();
	DrawFormatString(8, 24, 0xffffff,
		"プレイヤーの座標(%.2f,%.2f)", PlayerPos.x, PlayerPos.y);
	DrawFormatString(8, 40, 0xffffff,
		"敵の座標(%.2f,%.2f)", EnemyPos.x, EnemyPos.y);

}
