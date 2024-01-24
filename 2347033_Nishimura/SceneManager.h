#pragma once
class SceneManager
{
public:
	SceneManager();
	virtual~SceneManager();

	enum Scene
	{
		Title,
		S_Option,
		Playing,
		End
	};


void ChangeScene(Scene);
virtual void SceneUpdate()=0;
virtual void SceneDraw()=0;






};

