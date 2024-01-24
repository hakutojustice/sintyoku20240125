#include "Enemy.h"
#include "DxLib.h"
#include "Map.h"
#include "Player.h"

namespace
{
    //マップのサイズ
    constexpr int kWidth = 32;
    constexpr int kHeight = 32;

    //移動
    constexpr float kMove = 10.0f;

    //敵の数
    constexpr float kNumber = 5;


}

Enemy::Enemy() :
    m_x(1700.0f),
    m_y(704.0f),
    m_moveX(0.0f),
    m_moveY(0.0f)
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
    m_x -= kMove;

    if (m_x == 0)
    {
        m_x = 1600;
    }
    unsigned int color = 0xffff00;
    DrawBox(m_x, m_y, m_x + kWidth, m_y + kHeight, color, true);
}

