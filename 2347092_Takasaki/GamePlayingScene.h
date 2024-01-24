#pragma once
#include "Scene.h"
#include <string>
#include <vector>
#include <map>

class SceneMain;

class GamePlayingScene : public Scene
{
public:
    GamePlayingScene(SceneManager& manager);
    ~GamePlayingScene();
    virtual void Update();
    virtual void Draw();

private:
    
  
    int m_btnFrame = 0;

    int m_frame = 0;
    float m_fps = 0.0f;

    SceneMain* m_Scene;

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (GamePlayingScene::*)();
    using DrawFunc_t = void (GamePlayingScene::*)();
    UpdateFunc_t m_updateFunc = nullptr;
    DrawFunc_t m_drawFunc = nullptr;

    // �X�V�֐�
    void FadeInUpdate();
    void NormalUpdate();
    void FadeOutUpdate();

    // �`��֐�
    void FadeDraw();
    void NormalDraw();
};

