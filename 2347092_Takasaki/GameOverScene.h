#pragma once
#include "Scene.h"

class GameOverScene : public Scene
{
public:
    GameOverScene(SceneManager& mgr);
    ~GameOverScene();
    virtual void Update();
    virtual void Draw();

private:
   
    int m_btnFrame = 0;
    int m_frame;

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (GameOverScene::*)();
    using DrawFunc_t = void (GameOverScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // �X�V��Ԃ�\���֐�
    void FadeInUpdate();
    void NormalUpdate();
    void FadeOutUpdate();

    // �`���Ԃ�\���֐�
    void FadeDraw();
    void NormalDraw();
};

