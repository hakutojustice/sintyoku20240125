#include "Shot.h"

void Shot::Inti()
{
	//弾のグラフィックをメモリにロード
	ShotGraph = LoadGraph("date/Shot.png");

	//弾のグラフィックサイズをえる
	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//弾が画面上に存在しているか保持する変数に「存在していない」を意味する0を代入しておく
	ShotFlag = 0;
}

void Shot::Update(Player& player, Enemy& enemy)
{
	//←を押していて、弾が描画されていない時
	//if (CheckHitKey(KEY_INPUT_LEFT) == 1 && ShotFlag == 0)
	//{
	//	//プレイヤーと弾の画像のサイズを得る
	//	GetGraphSize(player.PlayerGraph, &player.PlayerW, &player.PlayerH);
	//	GetGraphSize(ShotGraph, &ShotW, &ShotH);

	//	//弾の位置をセット、位置はプレイヤーの中心にする
	//	ShotX = (player.PlayerW - ShotW) / 2 + player.PlayerX;
	//	ShotY = (player.PlayerH - ShotH) / 2 + player.PlayerY;

	//	ShotFlag = 1;
	//}

	//弾が描画しているとき
	//if (ShotFlag == 1)
	//{
	//	//弾とエネミーの当たり判定
	//	if (((ShotX > enemy.X && ShotY < enemy.X + enemy.W) ||
	//		(enemy.X > ShotX && enemy.X < ShotX + ShotW)) &&
	//		((ShotY > enemy.Y && ShotY < enemy.Y + enemy.H) ||
	//			(enemy.Y > ShotY && enemy.Y < ShotY + ShotH)))
	//	{
	//		//接触している場合は当たったエネミーの存在を消す
	//		
	//	}
	//}
}

void Shot::Draw()
{
	//弾の移動
	if (ShotFlag == 1)
	{
		//弾の30ドット上に移動させる
		ShotX += 30;

		//画面外に出てしまった場合は存在状態を保持している変数に0(存在しない)を代入する
		if (ShotX > 1600)
		{
			ShotFlag = 0;
		}
		//画面に弾を描画する
		DrawGraph(ShotX, ShotY, ShotGraph, false);
	}
}
