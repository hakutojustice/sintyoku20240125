#pragma once
#include "Scene.h"
class ClearScene : public Scene
{
public:
    ClearScene(SceneManager& mgr);
    ~ClearScene();
    virtual void Update();
    virtual void Draw();

private:

    int m_btnFrame = 0;
    int m_frame;

    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (ClearScene::*)();
    using DrawFunc_t = void (ClearScene::*)();
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

