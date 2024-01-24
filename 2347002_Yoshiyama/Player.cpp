//プレイヤーのソースファイル

//ヘッダファイルの読み込み
#include <DxLib.h>
#include "Game.h"
#include "SceneMain.h"
#include "Pad.h"
#include "Player.h"


//このファイル内でしか使えない関数表記
namespace
{
	//移動速度
	constexpr float kSpeed = 1.0f;

	//キャラクターのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	//半分のサイズ
	constexpr int kGraphHalfWidth = kGraphWidth / 2.0f;
	constexpr int kGraphHalfHeight = kGraphHeight / 2.0f;

	//キャラクターアニメーション
	constexpr int kUseFrame[] = { 0,1,2,1 };

	//アニメーション1コマのフレーム数
	constexpr int kAnimeFrameNum = 12;

	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimeFrameNum;
	// _countof()で配列のサイズを取得できる
	// _countof(kUseFrame)
//ダメージ演出フレーム数
	constexpr int kDamageFrame = 60;

}
//コンストラクタ
Player::Player() :
	m_handle(-1),
	m_pos(400, 500),//本来何ら400、685
	m_dir(kDirDown),
	m_walkAnimeFrame(kAnimeFrameNum),
	m_damageFrame(0),
	y_prev(0),
	y_temp(0),
	JumpPower(1),
	m_MoveDir(0, 3),
	Jump(0),
	Time(0),
	m_Move(0, 0),
	num(1)
{
}
//デストラクタ
Player::~Player()
{
}
//初期化処理
void Player::Init()
{
	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);
	m_pos.x = 400;
	m_pos.y = 685;

}
//更新処理
void Player::Update()
{
	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x + i, m_pos.y + i, kGraphWidth, kGraphHeight);

	//ダメージ演出の進行
	m_damageFrame--;
	if (m_damageFrame < 0) m_damageFrame = 0;
	//パッドの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	bool isMove = false; //移動中かどうか


	/*操作キーから方向を作成*/
	//左押したら左移動　右も同様　同時の場合は片方が優先される
	if (pad & PAD_INPUT_LEFT)
	{
		m_MoveDir.x = -1;
		//m_dir = kDirLeft;
		//反転しない
		Reverse = true;
		isMove = true;
	}
	else if (pad & PAD_INPUT_RIGHT)
	{
		m_MoveDir.x = 1;
		//m_dir = kDirRight;
		//反転する
		Reverse = false;
		isMove = true;
	}
	else
	{
		m_MoveDir.x = 0;
	}
	m_Move.x = m_MoveDir.x * 1;


	/*落下*/
	//落下処理//
	if (m_isToFloorFlag == false)
	{
		if (pad & PAD_INPUT_1 && JumpFlag == false && LastHitKey == false)
		{
			JumpFlag = true;
		}
		//時間の処理をして40秒以下なら上に上がり、40秒以上80秒以下なら下に下がる
		//それを超えたら時間を0にして、連続ジャンプできないようにする
		if (m_isToFloorFlag == false)
		{
			if (JumpFlag == true)
			{
				//時間が20秒以下なら入る
				if (Time < 20)
				{
					Time++;
					//ジャンプ処理
					m_MoveDir.y = -3;
				}
				//時間が40秒になるまで入る
				else if (Time < 40)
				{
					Time++;
					m_MoveDir.y = 3;
				}
				//時間が40秒以上になったらelseに入る
				else
				{
					Time = 0;
					JumpFlag = false;
				}
			}
			//キーボード→Z　コントローラー→Aボタンを押したときの処理
			//連続ジャンプを防ぐための処理
			if (pad & PAD_INPUT_1)
			{
				LastHitKey = true;
			}
			else
			{
				LastHitKey = false;
			}
		}
	//上記の値をプレイヤーの座標に入れることで移動してることになる
	m_Move.y = m_MoveDir.y * 1;
	m_pos += m_Move;
	}


	if (m_isToFloorFlag == false)
	{
		//横の坂道変換
		//実装プログラムは下からの順番での実装
		if (JumpFlag == false)
		{
			if (m_pos.y > 610)
			{
				//一段目
				for (int x = 0; x <= Game::kScreenWidth; x++)
				{
					//Xの値と比較する
					//staticは変数変換
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 685 - x * 0.05f;
					}
				}
			}
			else if (m_pos.y > 490)
			{
				//二段目
				for (int x = 0; x <= Game::kScreenWidth - 100; x++)
				{
					//Xの値と比較する
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 490 + x * 0.05f;
					}
				}
			}
			else if (m_pos.y >= 360)
			{
				//三段目
				for (int x = 160; x <= Game::kScreenWidth; x++)
				{
					//Xの値と比較する
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 430 - x * 0.05f;
					}
				}
			}
			else if (m_pos.y >= 235)
			{
				//四段目
				for (int x = 0; x <= Game::kScreenWidth - 100; x++)
				{
					//Xの値と比較する
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 210 + x * 0.05f;
					}
				}
			}
			else if (m_pos.y >= 100)
			{
				//ゴール地点
				for (int x = 520; x <= 640; x++)
				{
					//Xの値と比較する
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y = 115;
						m_isGoal = true;
					}
				}
			}
		}
	}


	//縦のはしご変換
	//上のボタンを押すことで梯子を上る処理
	//製作プログラムはプレイヤーの移動方向での実装
	if (pad & PAD_INPUT_UP)
	{
		//pos.yの一番下の値と、一番上の値の上限を設定して
		//その範囲内では移動できるようにする

		//現在調査中//
		//PAD_INPUT_UPしたときにゆっくりなめらかに上がる処理をしたいが
		//一気に上がってしまう
		// 原因①　for文によって一回入ったらその回数上がるため一気に上がる
		// 原因②　if文内の処理ができていない
		// 原因③　そもそもプログラムが正常ではない
		// 原因④　その他

		//一段目右、三段目真ん中、三段目右が登れない --解決--
		// 原因①　座標判定の問題(そもそも入ってないから違うと思われ)
		// 原因②　ifのpos.yの範囲がおかしい(何回か確認したけど違う可能性あり。)
		// 原因③　その他

		//一段目一番左
		//pos.yが660よりも大きい値の時
		if (m_pos.y >= 600 && m_pos.x <= 550 && m_pos.y <=662)
		{
			//for文を回す　15回回すことでよこの範囲を決定する
			for (int x = 450; x <= 465; x++)
				//if (static_cast<int>(m_pos.x) >= 450 && static_cast<int>(m_pos.x) <= 465)
			{
				//梯子の上限
				if (m_pos.y >= 620)
					//for文を回す　30買いまわすことでyの移動量を決定する
					//for (int y = 680; y <= 740; y++)
				{
					m_isToFloorFlag = true;
					//上記の回したforのpos.x内の適した値があったらはいる
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y -= 5.0f;
					}
				}

			}
		}
		//一段目一番右
		//pos.yが620より大きい値の時
		else if (m_pos.y >= 520 && m_pos.x >= 800)
		{
			//for文を回す　15回転することで横の範囲を決定する
			for (int x = 1000; x <= 1015; x++)
			{
				//for文を回す　50回転することでyの移動量を決定する
				//for (int y = 660; y <= 760; y++)
				if (m_pos.y >= 542)
				{
					m_isToFloorFlag = true;
					//上記の回したforのpos.x内の適した値があったらはいる
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y -= 5.0f ;
					}
				}
			}
		}
		

		//二段目一番右
		//poy.yが520以下かつ500より大きい値の時
		if (m_pos.y <= 520 && m_pos.y >= 420)
		{
			//for文を回す　15回転することで横の範囲を決定する
			for (int x = 530; x <= 545; x++)
			{
				//for文を回す　75回転することでyの移動量を決定する
				//for (int y = 650; y <= 720; y++)
				if(m_pos.y >= 480)
				{
						m_isToFloorFlag = true;
					//上記の回したforのpos.x内の適した値があったらはいる
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;

					}
				}
			}
		}
		//二段目一番左
		//pos.yが400以下かつ330より大きい値の時
		else if (m_pos.y <= 510 && m_pos.y >= 480)
		{
			//for文を回す　15回転することでyの移動量を決定する
			for (int x = 350; x <= 365; x++)
			{
				//for文を回す　60回転することでyの移動量を決定する
				for (int y = 665; y <= 725; y++)
				{
					//上記の回したforのpos.x内の適した値があったらはいる
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//三段目一番左
		//下のほうのみ反応させるプログラムで書いている
		//pos.yが320以下かつ220より大きい値の時
		else if (m_pos.y <= 430 && m_pos.y >= 400 && m_pos.x <= 600)
		{
			//for文を回す　15回転することでyの移動量を決定する
			for (int x = 500; x <= 515; x++)
			{
				//for文を回す　30回転することでyの移動量を決定する
				for (int y = 380; y <= 410; y++)
				{
					//上記の回したforのpos.x内の適した値があったら入る
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//三段目真ん中
		else if (m_pos.y <= 400 && m_pos.y >= 370 && m_pos.x <= 800)
		{
			for (int x = 750; x <= 765; x++)
			{
				for (int y = 280; y <= 365; y++)
				{
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//三段目一番右
		else if (m_pos.y <= 400 && m_pos.y >= 360)
		{
			for (int x = 1000; x <= 1015; x++)
			{
				for (int y = 270; y <= 335; y++)
				{
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;
						m_isToFloorFlag = true;
					}
				}
			}
		}
		//ゴール地点
		else if (m_pos.y <= 240 && m_pos.y >= 190)
		{
			for (int x = 560; x <= 575; x++)
			{
				for (int y = 110; y <= 190; y++)
				{
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y--;

						m_isToFloorFlag = true;
					}
				}
			}
		}
	}



	//縦のはしごの処理
	//下ボタンを押すことで梯子を下りる処理
	if (pad & PAD_INPUT_DOWN)
	{
		//pos.yの一番下の値と一番上の値の上限を設定して
		//その範囲内では移動できるようにする

		//一段目一番左 --放置--
		if (m_pos.y >= 610 && m_pos.y <= 660)
		{
			//for文を回す　15回回すことで横の範囲を決定する。
			for (int x = 450; x <= 465; x++)
			{
				//梯子の条件
				if (m_pos.y <= 661)
				//for文を回す。30回まわすことでyの移動量を決定する
				//for (int y = 430; y <= 460; y++)
				{
					//上記の回したfor文のpos.x内の適した値があったら入る
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y++;
					}
				}
			}
		}
		else
		{
			m_isToFloorFlag = false;
		}
		//一段目一番左
		if (m_pos.y >= 520 && m_pos.y <= 640)
		{
			//for文を回す　15回回すことで横の範囲を決定する
			for (int x = 1000; x <= 1015; x++)
			{
				/*for (int y = 430; x <= 460; y++)*/
				if(m_pos.y >= 600)
				{
					//上記の回したfor文のpos.x内の適した値があったら入る
					if (static_cast<int>(m_pos.x) == x)
					{
						m_pos.y++;
					}
				}
			}
		}
		else
		{
			m_isToFloorFlag = false;
		}
	}

	//if (m_MoveDir.y <= 0.005)
	//{
	//m_MoveDir.y -= JumpPower;
	//}
	//if (JumpPower == -30)
	//{
	//	JumpPower = 0;
	//}
	//
	////落下速度を加える
	//if ((pad & PAD_INPUT_1) && (JumpFlag == false))
	//{
	//	for (Jump = 0; Jump <= 20; Jump++)
	//	{
	//	//Aボタンを押したらジャンプ
	//	m_MoveDir.y -= Jump;
	//	JumpFlag = true;
	//	Time = 0;
	//	JumpPower = 0;
	//	}
	//}

	//Time++;
	//JumpPower -= 1.0f;
	//if (Time >= 20)
	//{
	//	Time == 0;
	//	if (JumpFlag == true)
	//	{
	//		//m_MoveDir.y -= JumpPower;
	//	}
	//		JumpFlag = false;
	//}


	///*プレイヤーの座標の表示*/
	////DrawFormatString(65, 85, 0xffffff,"プレイヤーの座標(%.2f,%.2f)", m_pos.x, m_pos.y);


	///*プレイヤーの移動*/
	////長さの変更
	//m_MoveDir *= kSpeed;
	////座標にベクトルを足す
	////落下処理
	//m_pos.y += m_MoveDir.y;
	//



	//if (isMove)
	//{
	//	//長さの変更
	//	m_MoveDir *= kSpeed;
	//	//座標にベクトルを足す
	//	m_pos.x += m_MoveDir.x;
	//}



	// 縦軸の移動制限
	if (m_pos.y < kGraphHalfHeight)
		m_pos.y = kGraphHalfHeight;
	else if (Game::kScreenHeight - kGraphHalfHeight < m_pos.y)
		m_pos.y = Game::kScreenHeight - kGraphHalfHeight;
	// 横軸の移動制限
	if (m_pos.x < kGraphHalfWidth)
		m_pos.x = kGraphHalfWidth;
	else if (Game::kScreenWidth - kGraphHalfWidth < m_pos.x)
		m_pos.x = Game::kScreenWidth - kGraphHalfWidth;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kGraphWidth, kGraphHeight);
}
//描画処理
void Player::Draw() const
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ダメージ演出　2フレーム感覚で表示日表示切替
	//0：表示される
	//1：表示される
	//2：非表示
	//3：非表示
	//4：表示させる　...
	//%４することで01230123012301230123...に変換する
	if (m_damageFrame % 4 >= 2) return;

	int animeEle = m_walkAnimeFrame / kAnimeFrameNum;


	int srcX = kGraphWidth * kUseFrame[animeEle];
	int srcY = kGraphHeight * m_dir;

	//DrawBox(m_pos.x - kGraphHalfWidth,
	//	m_pos.y - kGraphHalfHeight,
	//	m_pos.x + kGraphHalfWidth,
	//	m_pos.y + kGraphHalfHeight,
	//	0xffffff, true);

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
		srcX, srcY,
		kGraphWidth, kGraphHeight,
		1.0, 0.0,
		m_handle, true, Reverse);
	///*DrawReverseGraph(m_pos.x, m_pos.y, m_handle, true,Reverse);*/


#ifdef  _DEBUG
	m_colRect.Draw(0xff0000, false);
#endif //_DEBUG



}
//ダメージ処理
void Player::OnDamage()
{
	//ダメージ演出支柱は再度食らわない
	if (0 < m_damageFrame)return;
	//演出フレーム数を設定する
	m_damageFrame = kDamageFrame;
}
//床の処理
void Player::OnFloor(Rect FloorRect)
{
	// m_Movepos.y = 0;
	/*float dis = FloorRect.GetCenter().y - m_colRect.GetCenter().y;
	float onFloor = FloorRect.GetHeight() * 0.5f - m_colRect.GetHeight() * 0.5f;
	m_pos.y -= (onFloor - dis);*/

	m_pos.y -= m_MoveDir.y;
}

void Player::OnEnemy(Rect EnemyRect)
{
	m_isEnemyhit = true;
}
