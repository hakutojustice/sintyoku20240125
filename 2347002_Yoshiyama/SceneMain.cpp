//シーン処理のソースファイル

//ヘッダファイルの読み込み
#include<DxLib.h>
#include<cassert>
#include "Pad.h"
#include "Rect.h"

#include "SceneMain.h"

#include "GamePart.h"


#include "Game.h"
//このファイルでしか使えない変数　using namespace std;
namespace
{
	//画面がワイプするのにかかるフレーム数
	constexpr int kWipeFrame = 30;
}
//コンストラクタ
SceneMain::SceneMain():
	m_shakeFrame(0),
	m_wipeFrame(0)
{
	//ゲーム画面描画先の生成
	//画面サイズと同じ大きさのグラフィックデータを生成する
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//グラフィックのロード
	m_GamePartHandle = LoadGraph("data/Player.png");
	assert(m_GamePartHandle != -1);
	m_enemyHandle = LoadGraph("data/Enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/Map.png");
	assert(m_bgHandle != -1);
	m_wallHandle = LoadGraph("data/Wall.png");
	assert(m_wallHandle != -1);

	//プレイヤーメモリの確保
	m_pgamePart = new Gamepart;
	



	//敵の準備
	//m_pEnemy(vector何もしなければサイズは0)
	

	//resize関数でkEnemyMaxだけデータを保存できるようにする
	
}
//デストラクタ
SceneMain::~SceneMain()
{
	//MakeScreenで生成したグラフィックを削除する
	DeleteGraph(m_gameScreenHandle);

	//メモリ削除
	DeleteGraph(m_GamePartHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_wallHandle);

	//プレイヤーのメモリ開放
	delete m_pgamePart;
	m_pgamePart = nullptr;
	

	//背景のメモリ開放
	delete m_pBg;
	m_pBg = nullptr;

	//メモリが確保されている敵を探して開放していく
}
//初期化処理
void SceneMain::Init()
{
	assert(m_pgamePart);//m_pPlayer == nullptrの場合とまる

	m_pgamePart->Init();
}
//終了処理
void SceneMain::End()
{
}
//更新処理
void SceneMain::Update()
{
	m_pgamePart->Update();



	////画面揺れのフレームカウントダウン
	//m_wipeFrame--;
}
//描画処理
void SceneMain::Draw() const
{

	//描画先スクリーンをクリアする
	///ClearDrawScreen();

	m_pgamePart->Draw();

	//デバック表示
	DrawString(8, 8, "SceneMain", 0xffffff);

	
	
}
//近くの敵の座標を取得する処理
Vec2 SceneMain::GetNearEemyPos(Vec2 pos) const
{
	//敵がいない場合は適当な座標を返す
	Vec2 result{ 0,0 };
	//最初の敵チェック済みフラグ
	bool isFirst = true;

	clsDx();
	//一番近い敵キャラクターの座標をresultに入れる
	///for(const auto& enemy : m_pEmemy)

	//すべての敵のチェックを行ったのでこいつが一位で確定
	return result;
}



void SceneMain::CreateEnemyToPlayer()
{
}
