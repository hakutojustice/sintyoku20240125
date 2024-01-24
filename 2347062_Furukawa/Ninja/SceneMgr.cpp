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
		//前のシーンがあったら
		//開放しておく
		delete scene_;
	}
	scene_ = nextScene;
}
