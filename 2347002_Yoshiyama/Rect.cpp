#include "Rect.h"
#include <DxLib.h>
#include <cassert>

//コンストラクタ
Rect::Rect() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f),
	radiusT(0)
{
}
//デストラクタ
Rect::~Rect()
{
}
//上下左右の当たり判定の範囲の線を引く
void Rect::Draw(unsigned int color, bool isFill) const
{
	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top), static_cast<int>(m_right), static_cast<int>(m_bottom),
		color, isFill);


}

//上下左右の当たり判定の範囲を決める
void Rect::SetLT(float left, float top, float width, float height)
{
	m_left = left;
	m_top = top;
	m_right = left + width;
	m_bottom = top + height;
}

//当たり判定の中心を決める
void Rect::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;
	m_top = y - height / 2;
	m_right = x + width / 2;
	m_bottom = y + height / 2;
}

////上で設定した当たり判定横の大きさを取得する
//float Rect::GetWidth() const
//{
//	assert(m_left <= m_right);	// 左右の座標入れ替わりチェック
//	return m_right - m_left;
//}
////上で設定した当たり判定の縦の大きさを取得する
//float Rect::GetHeight() const
//{
//	assert(m_top <= m_bottom);	// 上下の座標入れ替わりチェック
//	return m_bottom - m_top;
//}
////上で設定した当たり判定の中心を取得する
//Vec2 Rect::GetCenter() const
//{
//	return Vec2{ (m_left + m_right) / 2, (m_top + m_bottom) / 2 };
//}

//円と円の長さ
//float Rect::GetLineSenter() const
//{
//
//}


bool Rect::IsCollsion(const Rect& target)
{
	// 絶対に当たらないパターンをはじいていく
	//ターゲットの右端は、自分の左端より小さい(ターゲットは左側にいる)
	if (target.m_right < m_left) return false;
	//ターゲットの下は。自分の上より小さい(ターゲットは上側にいる)
	if (target.m_bottom < m_top) return false;
	//自分の右は、ターゲットの左寄り小さい(ターゲットは右側にいる)
	if (m_right < target.m_left) return false;
	//自分の下は、ターゲットの上より小さい(ターゲットは下側にいる)
	if (m_bottom < target.m_top) return false;

	// 当たらないパターン以外は当たっている
	return true;
}



//仮　坂道の当たり判定作成
