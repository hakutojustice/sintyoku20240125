#include "Player.h"
#include "WalkEnemy.h"
#include "DxLib.h"
#include "GraphMode.h"
#include<math.h>



class Shot;
GraphMode graph;

Player::Player():
	HP(10),
	Speed(1.0f),
	playerGraph(-1),
	Aiming(-1),
	AimingW(0),
	AimingH(0),
	MouseX(0),
	MouseY(0),
	PlayerWidth(16),
	PlayerHeight(16),
	PlayerX(640.00f / 12.0f),
	PlayerY(480.00f - 100.0f),
	ScrollX(0.0f),
	ScrollY(0.0f),
	PlayerShotFlag(false),
	PlayerW(0),
	PlayerH(0),
	Gravity(0),
	W(0),
	H(0),
	PlayerRight(false),
	PlayerDamage(false),
	Left(false),
	Right(false),
	PlayerRise(false),
	Count(0)
{
	//弾初期化
	memset(shot, 0, sizeof(shot));

	
}

Player::~Player()
{
}

void Player::Init(Shield& shield,Shot shot[])
{
	DrawGraph(PlayerX, PlayerY, playerGraph, true);

	BulletTime = 0;

	Aiming = LoadGraph("date/標準.png");

	HP = 10;
	Speed = 1.0f;
	AimingW = 0;
	AimingH = 0;
	MouseX = 0;
	MouseY = 0;
	PlayerWidth = 16;
	PlayerHeight = 16;
	PlayerX = 640.0f / 12.0f;
	PlayerY = 480.0f - 100.0f;
	ScrollX = 0.0f;
	ScrollY = 0.0f;
	PlayerShotFlag = false;
	PlayerW = 0;
	PlayerH = 0;
	W = 0;
	H = 0;
	Gravity = 0.3f;
	PlayerRight = false;
	PlayerDamage = false;
	Bullet = 12;
	Left = false;
	Right = false;
	PlayerRise = false;
	Count = 0;

	for (int i = 0; i < SHOT; i++)
	{
		shot[i].Graph = LoadGraph("date/銃弾.png");
	}
	

	shield.LeftFlag = false;
	shield.RightFlag = false;
	shield.ShieldGraph = LoadGraph("date/Shiled.png");
	shield.ShieldWidth = 3;
	shield.ShieldHeight = 30;
}

void Player::InitShot(Shot shot[])
{
	for (int i = 0; i < SHOT; i++)
	{
		shot[i].Flag = false;

		shot[i].Damage = 3;
	}
	
}

void Player::Update(Player& player,Map& map,Shield& shield)
{
	//常に重力を与える
	/*player.PlayerY += player.Gravity;*/

	//盾実装
	//下キーを押した時
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		//プレイヤーを動けなくする
		Left = true;
		Right = true;
		player.PlayerShotFlag = true;

		//左に盾を構える
		if (player.PlayerX > player.MouseX)
		{
			shield.LeftFlag = true;

			shield.RightFlag = false;
		}
		//右に盾を構える
		if (player.PlayerX < player.MouseX)
		{
			shield.RightFlag = true;

			shield.LeftFlag = false;
		}
	}
	//下キーを押してないとき
	else if (CheckHitKey(KEY_INPUT_DOWN) == false)
	{
		//盾を消す
		shield.LeftFlag = false;
		shield.RightFlag = false;

		Left = false;
		Right = false;
	}
	//左キーを押したとき
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		if (Left == false)
		{
			player.PlayerX -= Speed;
		}
		
		//左端から先にいかない
		if (player.PlayerX < 8.0f)
		{
			player.PlayerX = 8.0f;
		}
	}
	//右キーを押したとき
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		if (Right == false)
		{
			player.PlayerX += player.Speed;
		}

		//真ん中から先に行くと画面がついてくる
		if (player.PlayerX >= graph.GraphModeWIDTH / 4)
		{
			player.PlayerRight = true;
			player.PlayerX = graph.GraphModeWIDTH / 4;
		}

	}
	//移動してないと画面が止まる
	else if (player.PlayerX <= graph.GraphModeWIDTH / 2)
	{
		//停止中は画面のスクロールは行わない
		player.PlayerRight = false;
		
		
	}

	if (player.PlayerRight == true)
	{
		//プレイヤー操作からスクロール量を算出する
		player.ScrollX -= Speed;
		player.ScrollY = 0.0f;
	}
	
	//当たり判定の更新
	m_colRect.SetCenter(player.PlayerX, player.PlayerY, player.PlayerWidth, player.PlayerHeight);
	
	//マウスの座標取得
	GetMousePoint(&player.MouseX, &player.MouseY);

	if (player.PlayerDamage == true)
	{
		Count++;
	}
	//4フレーム後
	if (Count <= 224)
	{
		player.PlayerDamage = false;
		Count = 0;
	}
}


void Player::ShotUpdate(Player& player,Shot shot[], int shotSize)
{
	//マウスキー(左クリック)が押されると発射
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		//弾が入っていると撃てる
		if (player.Bullet > 0)
		{
			if (player.PlayerShotFlag == false)
			{

				for (int i = 0; i < shotSize; i++)
				{
					if (shot[i].Flag == false)
					{
						shot[i].Flag = true;
						shot[i].X = player.PlayerX;
						shot[i].Y = player.PlayerY;

						//弾の移動速度を設定する
						double sb, sbx, sby, ax, ay, sx, sy;

						sx = shot[i].X + shot[i].Width / 2;
						sy = shot[i].Y + shot[i].Height / 2;

						ax = player.MouseX + player.AimingW / 2;
						ay = player.MouseY + player.AimingH / 2;

						sbx = ax - sx;
						sby = ay - sy;

						sb = sqrt(sbx * sbx + sby * sby);

						//1フレームあたり10ドットで動く
						shot[i].AimX = sbx / sb * 10;
						shot[i].AimY = sby / sb * 10;

						player.Bullet--;

						//一つ弾を出したので弾を出すループから抜ける
						break;
					}
				}
				player.PlayerShotFlag = true;
			}
		}
		else if (player.Bullet <= 0)
		{
			DrawString(100, 100, "弾切れ", GetColor(255, 255, 255));
		}
	}
	else
	{
		player.PlayerShotFlag = false;
	}

	//右クリックで弾をリロード
	if (GetMouseInput() & MOUSE_INPUT_RIGHT)
	{
		player.PlayerShotFlag = true;

		player.Bullet = 12;
	}

}

void Player::Draw(Shield& shield, Player& player)
{	
	playerGraph = DrawCircle(player.PlayerX, player.PlayerY, 8, GetColor(255, 255, 255), true);

	//プレイヤーの当たり判定の表示
	player.m_colRect.Draw(GetColor(0, 0, 255), false);
	//標準の画像描画
	DrawGraph(MouseX - 10, MouseY - 10, Aiming, true);

	//左に盾を構える
	if (shield.LeftFlag == true)
	{
		//shield.RightFlag = false;

		DrawGraph(player.PlayerX - 12, player.PlayerY - 20, shield.ShieldGraph, true);
		//当たり判定の更新
		shield.m_colRect.SetCenter(player.PlayerX - 13, player.PlayerY - 5, shield.ShieldWidth + 3, shield.ShieldHeight);

		shield.m_colRect.Draw(GetColor(0, 0, 255), false);
	}
	//右に盾を構える
	if (shield.RightFlag == true)
	{
		//shield.LeftFlag = false;

		DrawGraph(player.PlayerX + 10, player.PlayerY - 20, shield.ShieldGraph, true);
		//当たり判定の更新
		shield.m_colRect.SetCenter(player.PlayerX + 12, player.PlayerY - 5, shield.ShieldWidth + 3, shield.ShieldHeight);

		shield.m_colRect.Draw(GetColor(0, 0, 255), false);

	}
}

void Player::DrawShot(Shot& shot)
{
	//弾の移動
	//発射してる弾数だけ
	if (shot.Flag)
	{
		//shot.Graph = LoadGraph("date/銃弾.png");

		DrawGraph(shot.X, shot.Y, shot.Graph, true);

		shot.X += shot.AimX;
		shot.Y += shot.AimY;

		//当たり判定の更新
		shot.m_colRect.SetCenter(shot.X, shot.Y, shot.Width, shot.Height);

		//画面の外にはみ出したらフラグを戻す
		if (shot.X > 640 || shot.X < 0 || shot.Y > 480 || shot.Y < 0)
		{
			shot.Flag = false;
			//DeleteGraph(shot.Graph);
		}

	}

	
}



	
