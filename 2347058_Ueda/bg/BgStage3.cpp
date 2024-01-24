#include "BgStage3.h"
#include "Player.h"
#include "DxLib.h"
#include "Game.h"

namespace
{
	// 背景画像のサイズ
	constexpr int kBgWidth = 576;
	constexpr int kBgHeight = 324;

	// マップチップ1つのサイズ
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// チップを置く数
	constexpr int kChipNumX = 80;
	constexpr int kChipNumY = 34;

	// マップの広さ
	constexpr int kMapWidth = kChipWidth * kChipNumX;
	constexpr int kMapHeight = kChipHeight * kChipNumY;
}

BgStage3::BgStage3()
{
	m_bgHandle = LoadGraph("data/image/BackGround/stage3.png");
}

BgStage3::~BgStage3()
{
	DeleteGraph(m_bgHandle);
}

void BgStage3::Init()
{
}

void BgStage3::Update()
{
}

void BgStage3::Draw()
{
	DrawRectRotaGraph(0, 0, 0, 0, kBgWidth, kBgHeight, 10.0f, 0.0f, m_bgHandle, true);
}
