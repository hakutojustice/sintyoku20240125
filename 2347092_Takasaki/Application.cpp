#include "Application.h"
#include "SceneManager.h"
#include "Title.h"
#include "FileManager.h"
#include <DxLib.h>
#include <cassert>

namespace
{
    constexpr int kScreenWidth =1600;
    constexpr int kScreenHeight = 900;
}

int MyLoadGraph(const TCHAR* path)
{
    int handle = LoadGraph(path);
    assert(handle != -1);
    return handle;
}

Application::Application()
{
    m_windowSize = Size{ kScreenWidth, kScreenHeight };
}

void Application::Terminate()
{
    DxLib_End();
}

float Application::GetGravity() const
{
    return 0.5f;
}

bool Application::Init()
{
    ChangeWindowMode(true); // �E�B���h�E���[�h�ɂ��܂�
    SetGraphMode(m_windowSize.w, m_windowSize.h, 1);
    SetWindowSizeChangeEnableFlag(FALSE, FALSE);

    SetGraphMode(1600, 900, 32);
    SetWindowSize(1600, 900);

    SetWindowText("�������A�N�V�����Q�[��");
    if (DxLib_Init() == -1)
    {
        return false;
    }
    SetDrawScreen(DX_SCREEN_BACK);

    return true;
}

void Application::Run()
{
    {// �X�R�[�v�������I�ɍ���Ă���
        
        SceneManager sceneManager;
        sceneManager.ChangeScene(std::make_shared<Title>(sceneManager));
        

        LONGLONG time;
        while (ProcessMessage() != -1)
        {
            // FPS�̌Œ�悤�ɊJ�n���̎��Ԃ��擾
            time = GetNowHiPerformanceCount();

            ClearDrawScreen();
            
            sceneManager.Update();
            sceneManager.Draw();
            ScreenFlip();

            // 60FPS�ɌŒ�
            while (16667 > GetNowHiPerformanceCount() - time) {};
        }
    }
    Terminate();
}

const Size& Application::GetWindowSize() const
{
    return m_windowSize;
}
