#pragma once
#include "Scene.h"

//タイトルシーンクラス
class TitleScene : public Scene
{
public:
	void Update(Input& input);
	void Draw();

};

