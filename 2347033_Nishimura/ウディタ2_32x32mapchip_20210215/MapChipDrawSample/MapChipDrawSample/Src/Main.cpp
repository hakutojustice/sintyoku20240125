#include <Windows.h>
#include "Engine/Engine.h"
#include "Engine/Graphics.h"
#include "Engine/Texture.h"
#include "Utility/Vec.h"
#include "Engine/Input.h"

#define STAGE_WIDTH (640)									// ステージの横幅
#define STAGE_HEIGHT (320)									// ステージの縦幅
#define MAPCHIP_WIDTH (64)									// マップチップの横幅
#define MAPCHIP_HEIGHT (64)									// マップチップの縦幅
#define MAP_SIZE_WIDTH (STAGE_WIDTH / MAPCHIP_WIDTH)		// MAPの横幅(値はチップ数)
#define MAP_SIZE_HEIGHT (STAGE_HEIGHT / MAPCHIP_HEIGHT)		// MAPの縦幅(値はチップ数)

// マップチップ配列 (値はチップ画像に対応)
int g_MapChipList[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH]
{
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 3, 3, 0, 0, 1},
	{ 1, 0, 2, 2, 0, 0, 0, 0, 0, 1},
	{ 1, 0, 0, 0, 0, 0, 4, 4, 0, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void DrawMapChip()
{
	Texture* texture_data = GetTexture(TextureList::MapChip);

	if (texture_data == nullptr)
	{
		return;
	}

	// テクスチャのサイズとマップチップのサイズから横と縦のチップ数を割り出す
	int width_chip_num = texture_data->Width / MAPCHIP_WIDTH;
	int height_chip_num = texture_data->Height / MAPCHIP_HEIGHT;

	for (int y = 0; y < MAP_SIZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_SIZE_WIDTH; x++)
		{
			// チップ番号取得
			int chip_id = g_MapChipList[y][x];

			// 無効な値かをチェック
			if (chip_id == 0)
			{
				continue;
			}

			// chip_idからチップのテクスチャ座標を割り出す
			float tex_pos_x = (float)(chip_id % width_chip_num) * MAPCHIP_WIDTH;
			float tex_pos_y = (float)(chip_id / height_chip_num) * MAPCHIP_HEIGHT;

			// 描画座標を割り出す
			float position_x = (float)MAPCHIP_WIDTH * x;
			float position_y = (float)MAPCHIP_HEIGHT * y;

			// チップの描画
			DrawTextureUV(
				position_x,
				position_y,
				texture_data,
				tex_pos_x,
				tex_pos_y,
				MAPCHIP_WIDTH,
				MAPCHIP_HEIGHT
			);
		}
	}
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	// エンジンの初期化
	if (InitEngine(640, 320, "マップチップ描画サンプル") == false)
	{
		return 0;
	}

	Vec2 pos = Vec2(0.0f, 0.0f);
	LoadTexture("Res/MapChip.png", TextureList::MapChip);

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			UpdateInput();

			DrawStart();

			DrawMapChip();

			DrawEnd();
		}
	}

	// エンジン終了
	EndEngine();

	return 0;
}

