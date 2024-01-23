//�v���C���[�̃\�[�X�t�@�C��

//�w�b�_�t�@�C���̓ǂݍ���
#include <DxLib.h>
#include "Game.h"
#include "SceneMain.h"
#include "Pad.h"
#include "Player.h"


//���̃t�@�C�����ł����g���Ȃ��֐��\�L
namespace
{
	//�ړ����x
	constexpr float kSpeed = 1.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	//�����̃T�C�Y
	constexpr int kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr int kGraphHalfHeight = kGraphHeight / 2.0f;

	//�L�����N�^�[�A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,1 };

	//�A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimeFrameNum = 12;

	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimeFrameNum;
	// _countof()�Ŕz��̃T�C�Y���擾�ł���
	// _countof(kUseFrame)
//�_���[�W���o�t���[����
	constexpr int kDamageFrame = 60;

}
//�R���X�g���N�^
Player::Player() :
	m_handle(-1),
	m_pos(400, 500),//�{������400�A685
	m_dir(kDirDown),
	m_walkAnimeFrame(kAnimeFrameNum),
	m_damageFrame(0),
	y_prev(0),
	y_temp(0),
	JumpPower(1),
	m_MoveDir(0, 3),
	Jump(0),
	Time(0),
	m_Move(0, 0),
	num(1)
{
}
//�f�X�g���N�^
Player::~Player()
{
}
//����������
void Player::Init()
{
	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);
	m_pos.x = 400;
	m_pos.y = 685;

}
//�X�V����
void Player::Update()
{
	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x + i, m_pos.y + i, kGraphWidth, kGraphHeight);

	//�_���[�W���o�̐i�s
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;
	//�p�b�h�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	bool isMove = false; //�ړ������ǂ���


	/*����L�[����������쐬*/
	//���������獶�ړ��@�E�����l�@�����̏ꍇ�͕Е����D�悳���
	if (pad & PAD_INPUT_LEFT)
	{
		m_MoveDir.x = -1;
		//m_dir = kDirLeft;
		//���]���Ȃ�
		Reverse = true;
		isMove = true;
	}
	else if (pad & PAD_INPUT_RIGHT)
	{
		m_MoveDir.x = 1;
		//m_dir = kDirRight;
		//���]����
		Reverse = false;
		isMove = true;
	}
	else
	{
		m_MoveDir.x = 0;
	}
	m_Move.x = m_MoveDir.x * 1;


	/*����*/
	//��������//
	if (m_isToFloorFlag == false)
	{
		if (pad & PAD_INPUT_1 && JumpFlag == false && LastHitKey == false)
		{
			JumpFlag = true;
		}
		//���Ԃ̏���������40�b�ȉ��Ȃ��ɏオ��A40�b�ȏ�80�b�ȉ��Ȃ牺�ɉ�����
		//����𒴂����玞�Ԃ�0�ɂ��āA�A���W�����v�ł��Ȃ��悤�ɂ���
		if (m_isToFloorFlag == false)
		{
			if (JumpFlag == true)
			{
				//���Ԃ�20�b�ȉ��Ȃ����
				if (Time < 20)
				{
					Time++;
					//�W�����v����
					m_MoveDir.y = -3;
				}
				//���Ԃ�40�b�ɂȂ�܂œ���
				else if (Time < 40)
				{
					Time++;
					m_MoveDir.y = 3;
				}
				//���Ԃ�40�b�ȏ�ɂȂ�����else�ɓ���
				else
				{
					Time = 0;
					JumpFlag = false;
				}
			}
			//�L�[�{�[�h��Z�@�R���g���[���[��A�{�^�����������Ƃ��̏���
			//�A���W�����v��h�����߂̏���
			if (pad & PAD_INPUT_1)
			{
				LastHitKey = true;
			}
			else
			{
				LastHitKey = false;
			}
		}
	//��L�̒l���v���C���[�̍��W�ɓ���邱�Ƃňړ����Ă邱�ƂɂȂ�
	m_Move.y = m_MoveDir.y * 1;
	m_pos += m_Move;
	}


	if (m_isToFloorFlag == false)
	{
		//���̍⓹�ϊ�
		//�����v���O�����͉�����̏��Ԃł̎���
		if (JumpFlag == false)
		{
			if (m_pos.y > 610)
			{
				//��i��
				for (int x = 0; x <= Game::kScreenWidth; x++)
				{
					//X�̒l�Ɣ�r����
					//static�͕ϐ��ϊ�
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 685 - x * 0.05f;
					}
				}
			}
			else if (m_pos.y > 490)
			{
				//��i��
				for (int x = 0; x <= Game::kScreenWidth - 100; x++)
				{
					//X�̒l�Ɣ�r����
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 490 + x * 0.05f;
					}
				}
			}
			else if (m_pos.y >= 360)
			{
				//�O�i��
				for (int x = 160; x <= Game::kScreenWidth; x++)
				{
					//X�̒l�Ɣ�r����
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 430 - x * 0.05f;
					}
				}
			}
			else if (m_pos.y >= 235)
			{
				//�l�i��
				for (int x = 0; x <= Game::kScreenWidth - 100; x++)
				{
					//X�̒l�Ɣ�r����
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 210 + x * 0.05f;
					}
				}
			}
			else if (m_pos.y >= 100)
			{
				//�S�[���n�_
				for (int x = 520; x <= 640; x++)
				{
					//X�̒l�Ɣ�r����
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 115;
						m_isGoal = true;
					}
				}
			}
		}
	}


	//�c�̂͂����ϊ�
	//��̃{�^�����������ƂŒ�q����鏈��
	//����v���O�����̓v���C���[�̈ړ������ł̎���
	if (pad & PAD_INPUT_UP)
	{
		//pos.y�̈�ԉ��̒l�ƁA��ԏ�̒l�̏����ݒ肵��
		//���͈͓̔��ł͈ړ��ł���悤�ɂ���

		//���ݒ�����//
		//PAD_INPUT_UP�����Ƃ��ɂ������Ȃ߂炩�ɏオ�鏈������������
		//��C�ɏオ���Ă��܂�
		// �����@�@for���ɂ���Ĉ��������炻�̉񐔏オ�邽�߈�C�ɏオ��
		// �����A�@if�����̏������ł��Ă��Ȃ�
		// �����B�@���������v���O����������ł͂Ȃ�
		// �����C�@���̑�

		//��i�ډE�A�O�i�ڐ^�񒆁A�O�i�ډE���o��Ȃ� --����--
		// �����@�@���W����̖��(�������������ĂȂ�����Ⴄ�Ǝv���)
		// �����A�@if��pos.y�͈̔͂���������(���񂩊m�F�������ǈႤ�\������B)
		// �����B�@���̑�

		//��i�ڈ�ԍ�
		//pos.y��660�����傫���l�̎�
		if (m_pos.y >= 600 && m_pos.x <= 550 && m_pos.y <=662)
		{
			//for�����񂷁@15��񂷂��Ƃł悱�͈̔͂����肷��
			for (int x = 450; x <= 465; x++)
				//if (static_cast<int>(m_pos.x) >= 450 && static_cast<int>(m_pos.x) <= 465)
			{
				//��q�̏��
				if (m_pos.y >= 620)
					//for�����񂷁@30�����܂킷���Ƃ�y�̈ړ��ʂ����肷��
					//for (int y = 680; y <= 740; y++)
				{
					m_isToFloorFlag = true;
					//��L�̉񂵂�for��pos.x���̓K�����l����������͂���
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y -= 5.0f;
					}
				}

			}
		}
		//��i�ڈ�ԉE
		//pos.y��620���傫���l�̎�
		else if (m_pos.y >= 520 && m_pos.x >= 800)
		{
			//for�����񂷁@15��]���邱�Ƃŉ��͈̔͂����肷��
			for (int x = 1000; x <= 1015; x++)
			{
				//for�����񂷁@50��]���邱�Ƃ�y�̈ړ��ʂ����肷��
				//for (int y = 660; y <= 760; y++)
				if (m_pos.y >= 542)
				{
					m_isToFloorFlag = true;
					//��L�̉񂵂�for��pos.x���̓K�����l����������͂���
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y -= 5.0f ;
					}
				}
			}
		}
		

		//��i�ڈ�ԉE
		//poy.y��520�ȉ�����500���傫���l�̎�
		if (m_pos.y <= 520 && m_pos.y >= 420)
		{
			//for�����񂷁@15��]���邱�Ƃŉ��͈̔͂����肷��
			for (int x = 530; x <= 545; x++)
			{
				//for�����񂷁@75��]���邱�Ƃ�y�̈ړ��ʂ����肷��
				//for (int y = 650; y <= 720; y++)
				if(m_pos.y >= 480)
				{
						m_isToFloorFlag = true;
					//��L�̉񂵂�for��pos.x���̓K�����l����������͂���
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;

					}
				}
			}
		}
		//��i�ڈ�ԍ�
		//pos.y��400�ȉ�����330���傫���l�̎�
		else if (m_pos.y <= 510 && m_pos.y >= 480)
		{
			//for�����񂷁@15��]���邱�Ƃ�y�̈ړ��ʂ����肷��
			for (int x = 350; x <= 365; x++)
			{
				//for�����񂷁@60��]���邱�Ƃ�y�̈ړ��ʂ����肷��
				for (int y = 665; y <= 725; y++)
				{
					//��L�̉񂵂�for��pos.x���̓K�����l����������͂���
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//�O�i�ڈ�ԍ�
		//���̂ق��̂ݔ���������v���O�����ŏ����Ă���
		//pos.y��320�ȉ�����220���傫���l�̎�
		else if (m_pos.y <= 430 && m_pos.y >= 400 && m_pos.x <= 600)
		{
			//for�����񂷁@15��]���邱�Ƃ�y�̈ړ��ʂ����肷��
			for (int x = 500; x <= 515; x++)
			{
				//for�����񂷁@30��]���邱�Ƃ�y�̈ړ��ʂ����肷��
				for (int y = 380; y <= 410; y++)
				{
					//��L�̉񂵂�for��pos.x���̓K�����l�������������
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//�O�i�ڐ^��
		else if (m_pos.y <= 400 && m_pos.y >= 370 && m_pos.x <= 800)
		{
			for (int x = 750; x <= 765; x++)
			{
				for (int y = 280; y <= 365; y++)
				{
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//�O�i�ڈ�ԉE
		else if (m_pos.y <= 400 && m_pos.y >= 360)
		{
			for (int x = 1000; x <= 1015; x++)
			{
				for (int y = 270; y <= 335; y++)
				{
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//�S�[���n�_
		else if (m_pos.y <= 240 && m_pos.y >= 190)
		{
			for (int x = 560; x <= 575; x++)
			{
				for (int y = 110; y <= 190; y++)
				{
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;

						m_isToFloorFlag = true;
					}
				}
			}
		}
	}



	//�c�̂͂����̏���
	//���{�^�����������ƂŒ�q������鏈��
	if (pad & PAD_INPUT_DOWN)
	{
		//pos.y�̈�ԉ��̒l�ƈ�ԏ�̒l�̏����ݒ肵��
		//���͈͓̔��ł͈ړ��ł���悤�ɂ���

		//��i�ڈ�ԍ� --���u--
		if (m_pos.y >= 610 && m_pos.y <= 660)
		{
			//for�����񂷁@15��񂷂��Ƃŉ��͈̔͂����肷��B
			for (int x = 450; x <= 465; x++)
			{
				//��q�̏���
				if (m_pos.y <= 661)
				//for�����񂷁B30��܂킷���Ƃ�y�̈ړ��ʂ����肷��
				//for (int y = 430; y <= 460; y++)
				{
					//��L�̉񂵂�for����pos.x���̓K�����l�������������
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y++;
					}
				}
			}
		}
		else
		{
			m_isToFloorFlag = false;
		}
		//��i�ڈ�ԍ�
		if (m_pos.y >= 520 && m_pos.y <= 640)
		{
			//for�����񂷁@15��񂷂��Ƃŉ��͈̔͂����肷��
			for (int x = 1000; x <= 1015; x++)
			{
				/*for (int y = 430; x <= 460; y++)*/
				if(m_pos.y >= 600)
				{
					//��L�̉񂵂�for����pos.x���̓K�����l�������������
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y++;
					}
				}
			}
		}
		else
		{
			m_isToFloorFlag = false;
		}
	}

	//if (m_MoveDir.y <= 0.005)
	//{
	//m_MoveDir.y -= JumpPower;
	//}
	//if (JumpPower == -30)
	//{
	//	JumpPower = 0;
	//}
	//
	////�������x��������
	//if ((pad & PAD_INPUT_1) && (JumpFlag == false))
	//{
	//	for (Jump = 0; Jump <= 20; Jump++)
	//	{
	//	//A�{�^������������W�����v
	//	m_MoveDir.y -= Jump;
	//	JumpFlag = true;
	//	Time = 0;
	//	JumpPower = 0;
	//	}
	//}

	//Time++;
	//JumpPower -= 1.0f;
	//if (Time >= 20)
	//{
	//	Time == 0;
	//	if (JumpFlag == true)
	//	{
	//		//m_MoveDir.y -= JumpPower;
	//	}
	//		JumpFlag = false;
	//}


	///*�v���C���[�̍��W�̕\��*/
	////DrawFormatString(65, 85, 0xffffff,"�v���C���[�̍��W(%.2f,%.2f)", m_pos.x, m_pos.y);


	///*�v���C���[�̈ړ�*/
	////�����̕ύX
	//m_MoveDir *= kSpeed;
	////���W�Ƀx�N�g���𑫂�
	////��������
	//m_pos.y += m_MoveDir.y;
	//



	//if (isMove)
	//{
	//	//�����̕ύX
	//	m_MoveDir *= kSpeed;
	//	//���W�Ƀx�N�g���𑫂�
	//	m_pos.x += m_MoveDir.x;
	//}



	// �c���̈ړ�����
	if (m_pos.y < kGraphHalfHeight)
		m_pos.y = kGraphHalfHeight;
	else if (Game::kScreenHeight - kGraphHalfHeight < m_pos.y)
		m_pos.y = Game::kScreenHeight - kGraphHalfHeight;
	// �����̈ړ�����
	if (m_pos.x < kGraphHalfWidth)
		m_pos.x = kGraphHalfWidth;
	else if (Game::kScreenWidth - kGraphHalfWidth < m_pos.x)
		m_pos.x = Game::kScreenWidth - kGraphHalfWidth;

	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);
}
//�`�揈��
void Player::Draw() const
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�_���[�W���o�@2�t���[�����o�ŕ\�����\���ؑ�
	//0�F�\�������
	//1�F�\�������
	//2�F��\��
	//3�F��\��
	//4�F�\��������@...
	//%�S���邱�Ƃ�01230123012301230123...�ɕϊ�����
	if (m_damageFrame % 4 >= 2) return;

	int animeEle = m_walkAnimeFrame / kAnimeFrameNum;


	int srcX = kGraphWidth * kUseFrame[animeEle];
	int srcY = kGraphHeight * m_dir;

	//DrawBox(m_pos.x - kGraphHalfWidth,
	//	m_pos.y - kGraphHalfHeight,
	//	m_pos.x + kGraphHalfWidth,
	//	m_pos.y + kGraphHalfHeight,
	//	0xffffff, true);

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		1.0, 0.0,
		m_handle, true, Reverse);
	///*DrawReverseGraph(m_pos.x, m_pos.y, m_handle, true,Reverse);*/


#ifdef  _DEBUG
	m_colRect.Draw(0xff0000, false);
#endif //_DEBUG



}
//�_���[�W����
void Player::OnDamage()
{
	//�_���[�W���o�x���͍ēx�H���Ȃ�
	if (0 < m_damageFrame)return;
	//���o�t���[������ݒ肷��
	m_damageFrame = kDamageFrame;
}
//���̏���
void Player::OnFloor(Rect FloorRect)
{
	// m_Movepos.y = 0;
	/*float dis = FloorRect.GetCenter().y - m_colRect.GetCenter().y;
	float onFloor = FloorRect.GetHeight() * 0.5f - m_colRect.GetHeight() * 0.5f;
	m_pos.y -= (onFloor - dis);*/

	m_pos.y -= m_MoveDir.y;
}

void Player::OnEnemy(Rect EnemyRect)
{
	m_isEnemyhit = true;
}
