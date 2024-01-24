#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "DxLib.h"

namespace
{
    //マップのサイズ
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//重力
	constexpr float kGravity = 0.5f;

	//ジャンプ力
	constexpr float kJumpAcc = -12.0f;

}

Player::Player():
	m_isJump(0.0f),
	m_x(320.0f),
	m_y(704.0f),
	m_moveX(0.0f),
	m_moveY(0.0f),
	m_damage(0.0f),
	PlayerFlog(0.0f)
{
}

void Player::Update(Enemy& enemy)
{
	// 上下左右キーでプレイヤー移動
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	PlayerFlog = 1;
	m_y -= m_isJump;
	m_isJump -= 1;

	// もし地面についていたら止まる
	if (m_y > 704)
	{
		m_y = 704;
		m_isJump = 0;
	}


	if ((pad & PAD_INPUT_1) && m_y == 704)
	{
		m_isJump = 20;
	}


	if (((m_x > enemy.m_x && m_x < enemy.m_x + kWidth) ||
		(enemy.m_x > m_x && enemy.m_x < m_x + kWidth)) &&
		((m_y > enemy.m_y && m_y < enemy.m_y + kHeight) ||
			(enemy.m_y > m_y && enemy.m_y < m_y + kHeight)))
	{
		// 接触している
		PlayerFlog = 0;
		//DrawString(0, 0, "当たった", 0xffffff);
	}
}

void Player::Draw()
{
	unsigned int color = 0xff0000;

	if (m_damage >= 3)
	{
		DrawBox(m_x, m_y, m_x + kWidth, m_y + kHeight, color, false);
	}
	else
	{
		DrawBox(m_x, m_y, m_x + kWidth, m_y + kHeight, color, true);
	}
}

