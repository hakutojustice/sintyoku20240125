//プレイ画面のヘッダファイル
#pragma once
//外部のクラスの呼び出し
class Player;
class Floor;
class Enemy;
class SceneMain;
//プロトタイプ宣言
class Gamepart
{
public:
	Gamepart();
	~Gamepart();

	void Init();
	void Update();
	void Draw();

private:
	//グラフィックのハンドル
	int m_GamePlayerHandle;
	int m_enemyHandle;
	int m_bgHandle;
	int m_wallHandle;

	bool m_isEnemyhit = false;
	bool m_isGoal = false;
	//プレイヤー
	Player* m_pPlayer;

	//床
	Floor* m_pFloor;

	//エネミー
	Enemy* m_pEnemy;
};

