//プレイヤーのヘッダファイル
#pragma once
//ヘッダファイルの読み込み
#include "Vec2.h"
#include "Rect.h"
//外部クラスの読み込み
class SceneMain;
//プロトタイプ宣言
class Player
{
public:
	//向いている方向
	enum Dir
	{
		kDirDown,	//下
		kDirLeft,	//左
		kDirRight,	//右
		kDirUp		//上
	};

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw() const;
	void PlayerMove();

	//メンバ変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	//プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	//プレイヤーの当たり判定を取得する
	Rect GetColRect() { return m_colRect; }

	bool GetGoalFlag () const { return m_isGoal; }

	void OnDamage();

	void OnFloor(Rect FloorRect);

	void OnEnemy(Rect EnemyRect);

private:
	SceneMain* m_pMain;
	
	int m_handle; //グラフィックのハンドル

	//表示位置
	Vec2 m_pos;
	Vec2 m_Jump;
	Vec2 m_MoveDir;
	Vec2 m_Move;
	//当たり判定用の矩形
	Rect m_colRect;

	//向いている方向
	Dir m_dir;
	//歩きアニメーション
	int m_walkAnimeFrame;
	
	//ダメージ受けてからのフレーム数
	//普段は0
	//当たった時にフレーム数を設定して
	//以降毎フレーム減らしていく
	int m_damageFrame;

	//ジャンプの処理
	int JumpPower;
	bool JumpFlag = false;
	bool LastHitKey = false;
	int Jump;

	//梯子を上っている時の処理
	bool m_isladderClimbFlag = false;

	//床を登っている時の処理
	bool m_isToFloorFlag = false;

	//
	int y_prev;
	int y_temp;

	//時間の処理
	int Time;
	int num;
	int i;

	//反転の処理
	bool Reverse = false;
	//敵にあったっ他場合のフラグ
	bool m_isEnemyhit = false;
	//ゴールにたどり着いた時の処理
	bool m_isGoal = false;

};

