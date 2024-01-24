#include <DxLib.h>
#include <cassert>
#include "Application.h"

#include "SceneManager.h"
#include "Title.h"
#include "GamePlayingScene.h"

// �f�o�b�O���O�֌W
#include <sstream>
#include <iomanip>

Title::Title(SceneManager& manager) :
	Scene(manager)
{
	
	m_fadeFrame = 60;
	m_updateFunc = &Title::FadeInUpdate;
	m_drawFunc = &Title::FadeDraw;
	m_handle = LoadGraph("data/logo/demo_logo_d_v.png");
	// output string stream
	// Debug���O�̕\��
	std::ostringstream oss;
	oss << "TitleScene handle=" << std::hex <<
		" , frame=" << std::dec << std::setw(4) << std::setfill('0') << m_fadeFrame <<
		" , FPS=" << std::fixed << std::setprecision(2) << GetFPS() << std::endl;
	OutputDebugStringA(oss.str().c_str());
}

Title::~Title()
{
	OutputDebugString("�^�C�g���V�[����delete����܂���\n");
}

void Title::Update()
{
	(this->*m_updateFunc)();
}

void Title::Draw()
{
	(this->*m_drawFunc)();
}

void Title::FadeInUpdate()
{
	m_fadeFrame--;
	if (m_fadeFrame <= 0) // �J�ڏ���
	{
		// ���̑J�ڐ�
		m_updateFunc = &Title::NormalUpdate;
		m_drawFunc = &Title::NormalDraw;

		
	}
}

void Title::NormalUpdate()
{
	
	m_updateFunc = &Title::FadeOutUpdate;
	m_drawFunc = &Title::FadeDraw;
	m_fadeFrame = 0;
	
	m_fadeFrame = m_fadeFrame + 8;
	m_frame++;
	GetJoypadInputState(DX_INPUT_KEY_PAD1);

	

	
}

void Title::FadeOutUpdate()
{
	m_fadeFrame++;
	if (60 <= m_fadeFrame)
	{
		m_manager.ChangeScene(std::make_shared<GamePlayingScene>(m_manager));
	}
}

void Title::FadeDraw()
{
	// �ʏ�̕`��
	DrawString(10, 100, "TitleScene", 0xffffff);

	// �t�F�[�h�Ö�
	int alpha = static_cast<int>(255 * (static_cast<float>(m_fadeFrame) / 60.0f));
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Title::NormalDraw()
{

	DrawString(10, 100, "TitleScene", 0xffffff);
	int dx = abs((m_fadeFrame + 640) % (640 * 2) - 640);
	int num = 200;
	float dy = abs((m_fadeFrame + num) % (num * 2) - num) * 0.1f;
	dy = dy * dy;
	DrawCircle(dx, static_cast<int>(dy), 10, 0xffaaaa, true);
	auto& app = Application::GetInstance();
	auto size = app.GetWindowSize();
	int idx = m_frame / 10 % 3;
	constexpr int kButtonSize = 16;
	
}
