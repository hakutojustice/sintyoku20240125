#pragma once
#include "Scene.h"
class Title : public Scene
{
public:
	Title(SceneManager& manager);
	~Title();
	virtual void Update();
	virtual void Draw();

private:
	
	int m_bottonFrame = 0;

	int m_frame = 0;

	int m_fadeFrame = 0;

	int m_handle;

	// �X�V�����o�֐��|�C���^
	void(Title::* m_updateFunc)();
	// �`�惁���o�֐��|�C���^
	using DrawFunc_t = void (Title::*)();
	DrawFunc_t m_drawFunc;

	// �X�V�֐�
	void FadeInUpdate();	// �t�F�[�h�C�����
	void NormalUpdate();	// �ʏ���
	void FadeOutUpdate();	// �t�F�[�h�A�E�g���

	// �`��֐�
	void FadeDraw();	// �t�F�[�h���`��
	void NormalDraw();	// ��t�F�[�h�`��
};

