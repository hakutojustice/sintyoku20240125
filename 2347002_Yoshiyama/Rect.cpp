#include "Rect.h"
#include <DxLib.h>
#include <cassert>

//�R���X�g���N�^
Rect::Rect() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f),
	radiusT(0)
{
}
//�f�X�g���N�^
Rect::~Rect()
{
}
//�㉺���E�̓����蔻��͈̔͂̐�������
void Rect::Draw(unsigned int color, bool isFill) const
{
	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top), static_cast<int>(m_right), static_cast<int>(m_bottom),
		color, isFill);


}

//�㉺���E�̓����蔻��͈̔͂����߂�
void Rect::SetLT(float left, float top, float width, float height)
{
	m_left = left;
	m_top = top;
	m_right = left + width;
	m_bottom = top + height;
}

//�����蔻��̒��S�����߂�
void Rect::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;
	m_top = y - height / 2;
	m_right = x + width / 2;
	m_bottom = y + height / 2;
}

////��Őݒ肵�������蔻�艡�̑傫�����擾����
//float Rect::GetWidth() const
//{
//	assert(m_left <= m_right);	// ���E�̍��W����ւ��`�F�b�N
//	return m_right - m_left;
//}
////��Őݒ肵�������蔻��̏c�̑傫�����擾����
//float Rect::GetHeight() const
//{
//	assert(m_top <= m_bottom);	// �㉺�̍��W����ւ��`�F�b�N
//	return m_bottom - m_top;
//}
////��Őݒ肵�������蔻��̒��S���擾����
//Vec2 Rect::GetCenter() const
//{
//	return Vec2{ (m_left + m_right) / 2, (m_top + m_bottom) / 2 };
//}

//�~�Ɖ~�̒���
//float Rect::GetLineSenter() const
//{
//
//}


bool Rect::IsCollsion(const Rect& target)
{
	// ��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	//�^�[�Q�b�g�̉E�[�́A�����̍��[��菬����(�^�[�Q�b�g�͍����ɂ���)
	if (target.m_right < m_left) return false;
	//�^�[�Q�b�g�̉��́B�����̏��菬����(�^�[�Q�b�g�͏㑤�ɂ���)
	if (target.m_bottom < m_top) return false;
	//�����̉E�́A�^�[�Q�b�g�̍���菬����(�^�[�Q�b�g�͉E���ɂ���)
	if (m_right < target.m_left) return false;
	//�����̉��́A�^�[�Q�b�g�̏��菬����(�^�[�Q�b�g�͉����ɂ���)
	if (m_bottom < target.m_top) return false;

	// ������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}



//���@�⓹�̓����蔻��쐬
