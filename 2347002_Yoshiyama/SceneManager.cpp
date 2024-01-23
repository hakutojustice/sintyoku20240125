////シーン処理のソースファイル
//
////ヘッダファイル読み込み
//#include "SceneManager.h"
//#include "SceneMain.h"
//
//#include "Pad.h"
//
////コンストラクタ
//SceneManager::SceneManager()
//{
//	//クラスのメモリを確保する
//	m_pMain = new SceneMain;
//}
//
////デストラクタ
//SceneManager::~SceneManager()
//{
//	//クラスのメモリを開放する
//	delete m_pMain;
//	m_pMain = nullptr;
//}
//
////初期化
//void SceneManager::Init()
//{
//	m_pMain->Init();
//}
//
////終了
//void SceneManager::End()
//{
//	m_pMain->End();
//}
//
////更新
//void SceneManager::Update()
//{
//	Pad::Update();
//
//	m_pMain->Update();
//}
//
////読み込み
//void SceneManager::Draw() const
//{
//	m_pMain->Draw();
//}
//
//void SceneManager::ChangeScene()
//{
//	if (m_pMain.empty()) {
//
//	}
//}
