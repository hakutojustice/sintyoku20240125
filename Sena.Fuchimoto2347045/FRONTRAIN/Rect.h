#pragma once
#include "Vec2.h"
class Rect
{
public:
	Rect();
	virtual ~Rect();

	//描画
	void Draw(unsigned int color, bool isFill);

	//左上座標と幅高さを指定
	void SetLT(float left, float top, float width, float bottom);

	//中心座標と幅高さを指定
	void SetCenter(float left, float top, float width, float height);

	//必要な情報を取得する
	float GetWidth() const;   //矩形の幅
	float GetHeight() const;  //矩形の高さ
	Vec2 GetCenter() const;   //矩形の中心座標

	//矩形同士のあたり判定
	bool IsCollision(const Rect& rect);

	//ブロックの当たり判定下
	bool IsCollisionBlockBottom(const Rect& rect);

private:
	float m_left;    //左上のX座標
	float m_top;     //左上のY座標
	float m_right;   //右下のX座標
	float m_bottom;  //右下のY座標
};

