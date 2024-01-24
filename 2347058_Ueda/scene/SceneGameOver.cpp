#include "SceneGameOver.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// ゲームオーバー文字表示位置
	constexpr int kGameOverPosX = 960;
	constexpr int kGameOverPosY = 300;

	// ゲームオーバー文字のサイズ
	constexpr int kGameOverSizeX = 1592;
	constexpr int kGameOverSizeY = 174;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 700;

	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 910;
	constexpr int kInitSelectPosY = 560;
	// 選択カーソルの移動量
	constexpr int kSelectmoveY = 145;
	// 選択カーソルのサイズ
	constexpr int kSelectSizeX = 500;
	constexpr int kSelectSizeY = 700;
}


SceneGameOver::SceneGameOver():
	m_select(kRetry),
	m_isSceneRetry(false),
	m_isSceneSelect(false),
	m_isSceneTitle(false)
{
	m_bgHandle = LoadGraph("data/image/BackGround/gameover.png");
	m_gameoverHandle = LoadGraph("data/image/UI/gameover.png");
	m_charHandle = LoadGraph("data/image/UI/gameoverSelect.png");
	m_selectHandle = LoadGraph("data/image/UI/select.png");
}

SceneGameOver::~SceneGameOver()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_gameoverHandle);
	DeleteGraph(m_charHandle);
	DeleteGraph(m_selectHandle);
}

void SceneGameOver::Init()
{
	m_isSceneRetry = false;
	m_isSceneSelect = false;
	m_isSceneTitle = false;
	m_select = kRetry;
	m_selectPos.x = kInitSelectPosX;
	m_selectPos.y = kInitSelectPosY;
}

void SceneGameOver::Update()
{
	// TODO:リトライできるようにする

	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSelectmoveY; // 選択カーソルを下に移動

		// 選択カーソルが一番下にだったら四角を一番上に戻す
		if (m_selectPos.y > kInitSelectPosY + kSelectmoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
	}
	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select + (kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSelectmoveY;	// 選択カーソルを上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSelectmoveY * (kSelectNum - 1);
		}
	}

	// Zキーを押したとき
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// 移動先を決定
		switch (m_select)
		{
		case kRetry:
			m_isSceneRetry = true;
			break;
		case kSelectStage:
			m_isSceneSelect = true;
			break;
		case kTitle:
			m_isSceneTitle = true;
		default:
			break;
		}
	}

#ifdef _DEBUG
	// Zキーを押したらステージ選択画面に遷移
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isSceneSelect = true;
	}
#endif

}

void SceneGameOver::Draw()
{
	// 背景表示
	DrawGraph(0, 0, m_bgHandle, false);
	//// クリア表示
	//DrawGraph(400, 200, m_gameoverHandle, true);
	//// 文字表示
	//DrawGraph(850, 550, m_charHandle, true);

	// ゲームオーバー表示
	DrawRectRotaGraph(kGameOverPosX, kGameOverPosY, 0, 0,kGameOverSizeX,kGameOverSizeY, 0.8f, 0.0f, m_gameoverHandle, true, false);
	// 文字表示
	DrawRectRotaGraph(kCharPosX, kCharPosY, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_charHandle, true, false);
	// 選択カーソルの表示
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y, 0, 0, kSelectSizeX, kSelectSizeY, 1.0f, 0.0f, m_selectHandle, true, false);

#ifdef _DEBUG
	DrawString(10, 10, "ゲームオーバー", 0xff0000);
#endif
}

void SceneGameOver::End()
{
}

