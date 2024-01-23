
//画面表示のヘッダファイル
#pragma once
//ヘッダファイル読み込み
#include "Vec2.h"
#include<Vector>
//名前空間の処理
using namespace std;

//クラス呼び出し
	class Gamepart;
	class Bg;
	class EnemyBase;
//プロトタイプ宣言
class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();
	
	void Init();
	void End();

	void Update();
	void Draw() const;

	//特定の座標から一番近くにいる敵の座標を返す関数
	Vec2 GetNearEemyPos(Vec2 pos) const;
	//樽を追加する関数
	//登録できなかった場合はfalseを返す
	//登録できなかった場合は内部でpShot開放する

private:
	//敵キャラクターの生成
	void CreateEnemyLeft();
	void CreateEnemyRight();
	void CreateEnemyToPlayer();

private:
	//グラフィックのハンドル
	int m_gameScreenHandle;
	
	int m_GamePartHandle;
	int m_enemyHandle;
	int m_bgHandle;
	int m_wallHandle;

	//プレイヤー
	Gamepart* m_pgamePart ;
	//背景
	Bg* m_pBg; 
	//敵

	//樽

	//画面ワイプ処理
	int m_wipeFrame;

	//敵の登場間隔

	//画面が揺れる演出
	int m_shakeFrame;
	
};

