//床の梯子の描画処理
#pragma once
//ヘッダファイルの読み込み
#include "Vec2.h"
#include "Rect.h"
//外部のクラスの読み込み
class SceneMain;
//プロトタイプ宣言
class Floor
{
public:
	Floor();
	~Floor();

	void Init();
	void Update();
	void Draw();
	Rect GetRect() const { return m_Rect; }

	//メンバ変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	//指定した矩形と当たっているか判定
	bool IsCol(Rect rect);

	SceneMain *m_pMain;

	//グラフィックのハンドル
	int m_handle;

	//壁の部品
	Vec2 m_Pos;
	Rect m_Rect;

	int m_height;
	int m_width;
	
	bool m_isGoal = false;

	


	int i;


};

