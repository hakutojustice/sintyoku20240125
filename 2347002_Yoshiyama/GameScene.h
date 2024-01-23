//ゲームシーンのヘッダファイル
#pragma once
//ヘッダファイルの読み込み
#include "GameCommon.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "MyGameLib.h"
#include "Player.h"

//クラスの読み込み
class SceneMain;
class Player;

class GameScene
{
private:
	//メンバ変数
	SceneKind _nextScene,_tempScene;//シーン更新用
	SceneMain* m_pSceneMain;
	Player* m_player;


public:
	/*コンストラクタ*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_tempScene(SceneKind::GAMESCENE)
	{
		//シーンのメモリの確保
		m_pSceneMain = new SceneMain;
	};
	//デストラクタ
	~GameScene()
	{
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
	}
	SceneKind Update()
	{
		m_pSceneMain->Update();
		/*シーン繊維処理*/
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}
		//敵と当たっていたらタイトル画面にする処理に今後実行していく
		

		return _nextScene;
	}
	void Draw()
	{
		//現在のシーン名を描画
		DrawString(8, 8, "SceneName:GameScene", GetColor(255, 255, 255));
		m_pSceneMain->Draw();
	}
	void Init()
	{
		//メンバ変数の初期化
		_nextScene = SceneKind::GAMESCENE;
		_tempScene = SceneKind::GAMESCENE;
		m_pSceneMain->Init();
	}
};
