#include "Rect.h"
#include "Dxlib.h"
#include<cassert>

Rect::Rect():
	m_left(0),
	m_top(0),
	m_right(0),
	m_bottom(0)
{
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int color, bool isFill)
{
	DrawBoxAA(static_cast<int>(m_left), static_cast<int>(m_top), static_cast<int>(m_right), static_cast<int>(m_bottom), color, isFill);
}

void Rect::SetLT(float left, float top, float width, float bottom)
{
	m_left = left;
	m_top = top;
	m_right = left + width;
	m_bottom = top + bottom;
}

void Rect::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;
	m_top = y - height / 2;
	m_right = x + width / 2;
	m_bottom = y + height / 2;
}

float Rect::GetWidth() const
{
	assert(m_right >= m_left);     //左右の座標けれ変わりチェック
	return m_right - m_left;
}

float Rect::GetHeight() const
{
	assert(m_bottom >= m_top);

	return m_bottom - m_top;
}

Vec2 Rect::GetCenter() const
{
	float x = 0.0f;
	float y = 0.0f;
	//中心座標
	x = (m_left + m_right) / 2;
	y = (m_top + m_bottom) / 2;

	return Vec2(x, y);
}

bool Rect::IsCollision(const Rect& rect)
{
	//絶対に当たらないパターンをはじいていく
	if (m_left > rect.m_right) return false;
	if (m_top > rect.m_bottom) return false;
	if (m_right < rect.m_left) return false;
	if (m_bottom < rect.m_top) return false;
	//当たらないパターン以外は当たっている

	return true;
}

bool Rect::IsCollisionBlockBottom(const Rect& rect)
{
	//キャラの足元が地面についていない状態
	if (m_bottom >= rect.m_top) return true;
	//他は地面についている状態判定
	return false;
}
