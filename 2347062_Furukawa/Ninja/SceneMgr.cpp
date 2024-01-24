#include "SceneMgr.h"
#include "Scene.h"

void SceneMgr::Upsate(Input& input)
{
	scene_->Update(input);
}

void SceneMgr::Draw()
{
	scene_->Draw();
}

void SceneMgr::ChangeScene(Scene* nextScene)
{
	if (scene_  != nullptr)
	{
		//�O�̃V�[������������
		//�J�����Ă���
		delete scene_;
	}
	scene_ = nextScene;
}
