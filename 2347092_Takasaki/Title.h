#pragma once
#include "Scene.h"
class Title : public Scene
{
public:
	Title(SceneManager& manager);
	~Title();
	virtual void Update();
	virtual void Draw();

private:
	
	int m_bottonFrame = 0;

	int m_frame = 0;

	int m_fadeFrame = 0;

	int m_handle;

	// 更新メンバ関数ポインタ
	void(Title::* m_updateFunc)();
	// 描画メンバ関数ポインタ
	using DrawFunc_t = void (Title::*)();
	DrawFunc_t m_drawFunc;

	// 更新関数
	void FadeInUpdate();	// フェードイン状態
	void NormalUpdate();	// 通常状態
	void FadeOutUpdate();	// フェードアウト状態

	// 描画関数
	void FadeDraw();	// フェード中描画
	void NormalDraw();	// 非フェード描画
};

