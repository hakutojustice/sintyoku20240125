//床や、柵の配置ソースファイル

//ヘッダファイル読み込み
#include "Floor.h"

#include "DxLib.h"
#include "Game.h"
#include "SceneMain.h"

//このファイル内専用の関数
namespace
{
	// キャラクターのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;
}


//コンストラクタ
Floor::Floor() :
	i(),
	m_handle(-1)
{
	m_Pos = { 200,600 };
}
//デストラクタ
Floor::~Floor()
{
}
//初期化処理
void Floor::Init()
{
	// 当たり判定の更新
	m_Rect.SetCenter(m_Pos.x, m_Pos.y, kGraphWidth, kGraphHeight);
}
//更新処理
void Floor::Update()
{
	// 当たり判定の更新
	m_Rect.SetCenter(m_Pos.x + i, m_Pos.y + i, kGraphWidth, kGraphHeight);
}
//描画処理
void Floor::Draw()
{
	//床画像の描画
	DrawRotaGraph(static_cast<int>(m_Pos.x), static_cast<int>(m_Pos.y)
		,1.5f, 1.5f,
		kGraphWidth, kGraphHeight,
		m_handle, true);
	
	//床を横に表示させる　(方向+-どれくらいの長さ(i)+-座標調整)
	for (i = 0; i < 1300; i++)
	{
		//for文は横の幅の長さ　これは固定
		//一段目
		for (float a = 0; a < 15; a++)
		{
			DrawPixel (m_Pos.x + i - 200, m_Pos.y  - i * 0.05 + a + 100, 0xffffff);
		}
		//二段目
		for (float b = 0; b < 15; b++)
		{
			DrawPixel(m_Pos.x - i + 980, m_Pos.y - i * 0.05  - b - 20, 0xffffff);
			
		}
		//三段目
		for (float c = 0; c < 15; c++)
		{
			DrawPixel(m_Pos.x + i - 40, m_Pos.y - i * 0.05 - c - 150, 0xffffff);
		}
		//四段目
		for (float d = 0; d < 15; d++)
		{
			DrawPixel(m_Pos.x - i + 980, m_Pos.y - i * 0.05 - d - 300, 0xffffff);
		}
	m_Rect.Draw(0x0000ff, false);
	}

	//梯子の表示
	for (i = 0; i < 15; i++)
	{
		//for文は縦の幅の長さ　これを調節して縦の長さを再現
		//一段目一番左
		for (float a = 0; a < 60; a++)
		{
			DrawPixel(m_Pos.x + i + 250, m_Pos.y - 1 - a  + 80, 0xff11ff);
			DrawPixel(m_Pos.x + i + 250, m_Pos.y - 1 - a - 0, 0xff11ff);
		}
		//一段目一番右
		for (float b = 0; b < 100; b++)
		{
			DrawPixel(m_Pos.x + i + 800, m_Pos.y - 1 - b + 60, 0xff11ff);
		}
		//二段目一番右
		for (float c = 0; c < 130; c++)
		{
			DrawPixel(m_Pos.x + i + 330, m_Pos.y - 1 - c - 50, 0xff11ff);
		}
		//二段目一番左
		for (float d = 0; d < 100; d++)
		{
			DrawPixel(m_Pos.x + i + 150, m_Pos.y - 1 - d - 65, 0xff11ff);
		}
		//三段目一番左
		for (float e = 0; e < 60; e++)
		{
			DrawPixel(m_Pos.x + i + 300, m_Pos.y - 1 - e - 180, 0xff11ff);
			DrawPixel(m_Pos.x + i + 300, m_Pos.y - 1 - e - 280, 0xff11ff);
		}
		//三段目真ん中
		for (float f = 0; f < 150; f++)
		{
			DrawPixel(m_Pos.x + i + 550, m_Pos.y - 1 - f - 180, 0xff11ff);
		}
		//三段目一番右
		for (float g = 0; g < 130; g++)
		{
			DrawPixel(m_Pos.x + i + 800, m_Pos.y - 1 - g - 190, 0xff11ff);
		}
	}

	//ゴール地点の床の表示
	for (i = 0; i < 15; i++)
	{
		//とらわれた姫ポジション  横方向
		for (float a = 0; a < 120; a++)
		{
			DrawPixel(m_Pos.x + a + 200, m_Pos.y - 1 + i - 460, 0xffffff);
		}
		//ゴール地点　横方向
		for (float b = 0; b < 120; b++)
		{
			DrawPixel(m_Pos.x + b + 320, m_Pos.y - 1 + i - 470, 0xffffff);
		}
		//ゴール手前のはしご　縦方向
		for (float c = 0; c < 120; c++)
		{
			DrawPixel(m_Pos.x + i + 360, m_Pos.y - 1 + c - 460, 0xff11ff);
		}
		////とらわれた姫ポジションはしご左側　縦方向
		//for (float d = 0; d < 190; d++)
		//{
		//	DrawPixel(m_Pos.x + i + 130, m_Pos.y - 1 + d - 400, 0xffffff);
		//	DrawPixel(m_Pos.x + i + 100, m_Pos.y - 1 + d - 400, 0xffffff);
		//}
	}


}

bool Floor::IsCol(Rect rect)
{
	return false;
}
