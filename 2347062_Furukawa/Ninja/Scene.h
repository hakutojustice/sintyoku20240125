#pragma once

class Input;
class SceneManager;

//シーン基底クラス
//いろんなシーンの基になるクラス

class Scene
{
public:

	//生成時にSceneManagerの参照を受け取っておく
	
	//SceneManagerの参照
	Scene(SceneManager& manager);

	//シーンの更新
	//入力オブジェクト
	virtual void Update(Input& input) = 0;
	virtual void Draw() = 0;
private:
	SceneManager& manager_;
};

