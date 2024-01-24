#pragma once
class Input;
class Scene;
//各シーンの遷移とそうさをコントロールするクラス
class SceneMgr
{
public:
	//持っているシーンのUpdate関数を呼び出す
	//入力クラス
	void Upsate(Input& input);
	//持っているシーンの描画Draw関数を呼び出す
	void Draw();
	//現在実行中のシーンを引数で定義されたシーンに切り替える
	//次のシーン
	void ChangeScene(Scene* nextScene);

private:
	Scene* scene_=nullptr;

};

