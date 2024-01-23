//エネミーのヘッダファイル
#pragma once
//ヘッダファイルの読み込み
#include "Vec2.h"
#include "Rect.h"
//外部クラスの読み込み
class SceneMain;

//プロトタイプ宣言
class Enemy
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
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw() const;
	void EmemyMove();

	//メンバ変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	//敵のの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }
	//プレイヤーの当たり判定を取得する
	Rect GetColRect() { return m_colRect; }

	void OnDamage();

	void OnFloor(Rect FloorRect);

	void OnPlayer(Rect PlayerRect);

	//敵キャラクターをスタートさせる

private:
	SceneMain* m_pMain;

	int m_handle;//グラフィックのハンドル
	int Time;

	//表示位置
	Vec2 m_pos;
	Vec2 m_MoveDir;
	Vec2 m_Move;
	//当たり判定用の矩形
	Rect m_colRect;
	Rect m_Rect;

	//向いている方向
	Dir m_dir;
	int Reverse = false;


	//歩きアニメーション
	int m_walkAnimeFrame;
	int i;
	

	bool m_isExist;//存在しているかどうかのフラグ(使用中かどうか)
	bool m_isPrevEnemyFlag;

};

