#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "DxLib.h"

namespace
{
    //�}�b�v�̃T�C�Y
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	//�d��
	constexpr float kGravity = 0.5f;

	//�W�����v��
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
	// �㉺���E�L�[�Ńv���C���[�ړ�
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	PlayerFlog = 1;
	m_y -= m_isJump;
	m_isJump -= 1;

	// �����n�ʂɂ��Ă�����~�܂�
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
		// �ڐG���Ă���
		PlayerFlog = 0;
		//DrawString(0, 0, "��������", 0xffffff);
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

