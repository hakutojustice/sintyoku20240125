//#include "animation.h"
//
//Animation SkyEnemy;    //SkyEnemyのアニメーション
//
////読み込み・ハンドル生成
//BOOL Animation_Init(VOID)
//{
//	//SkyEnemyのアニメーション
//	SkyEnemy = LoadAnimation(
//		GraphicPathSkyEnemy,
//		AnimSkyEnemyDivX,                 //アニメーション横分割数
//		AnimSkyEnemyDivY                  //アニメーション縦分割数
//	); if (AnimSkyEnemy.Handle[0] == -1) { return FALSE; }
//
//	return TRUE;
//}
//
////後始末
//VOID Animation_End(VOID)
//{
//	DeleteAnimation(AnimSkyEnemy);
//
//	return;
//}
//
////読み込みエラーメッセージ
//VOID AnimationLoadErrMessage(const char* path)
//{
//	//エラー用文字列
//	char ErrStr[AnimationPathStrMax];
//
//	//エラー用文字列の内容を空にする
//	for (int i = 0; i < AnimationPathStrMax; i++) { ErrStr[i] = '\0'; }
//
//	//エラー内容を連結して生成
//	sprintf_s(ErrStr, sizeof(ErrStr), "%s%s", path, AnimationLoadErrCap);
//
//	//パスが間違っているなどでインストールできない場合はエラー
//	MessageBox(
//		GetMainWindowHandle(),
//		ErrStr,
//		AnimationLoadErrTitle,
//		MB_OK);
//
//	return;
//}
//
////アニメーション読み込み
//Animation LoadAnimation(Graphic graphic, int XNum, int YNum)
//{
//	Animation animation;
//
//	//読み込んだ画像の情報を引き継ぐ
//	animation.g = graphic;
//
//	//画像の分割数を設定
//	animation.a.DivX = XNum;
//	animation.a.DivY = YNum;
//
//	//画像の幅と高さを再計算
//	animation.g.c.Width = animation.g.c.Width / XNum;
//	animation.g.c.Height = animation.g.c.Height / YNum;
//
//	//当たり判定も再計算
//	ReMakeCollRect(&animation.g);
//
//	//アニメーションのハンドル配列を動的確保
//	animation.Handle = (int*)calloc(XNum * YNum, sizeof(int));
//
//	//int型のポインタに型変換
//	//メモリを動的確保して値をゼロで初期化
//	//確保する要素の個数
//	//確保する要素のデータ型
//
//	//アニメーションを分割してメモリに読み込み
//	LoadDivGraph(
//		graphic.c.Path,          //アニメーションのパス
//		(XNum * YNum),        //分割総数
//		XNum, YNum,            //(横)分割数 - (縦)分割数
//		animation.g.c.Width,    //分割した1枚の幅
//		animation.g.c.Height,   //分割した1枚の高さ
//		animation.Handle       //連続したハンドル配列の先頭
//	);
//
//	//読み込みエラー
//	if (animation.Handle == NULL || animation.Handle[0] == -1)
//	{
//		AnimationLoadErrMessage(graphic.c.Path);
//	}
//
//	//メモリに読み込んだ画像はサイズを知りたいだけだから用済み
//	DeleteGraphic(graphic);
//
//	//ハンドルの要素数を初期化
//	animation.a.NowHandleIndex = 0;
//
//	//最初のアニメーションの要素数をセット
//	animation.g.Handle = animation.Handle[animation.a.NowHandleIndex];
//
//	return animation;
//
//}
//
////描画
//VOID DrawAnimation(Animation* animation)
//{
//	//画像描画
//	DrawGraphic(&animation->g);
//
//	//アニメーション中ならコマを進める
//	if (animation->a.IsAnimStartFlg == TRUE)
//	{
//		if (animation->a.FrameByFrameCnt < animation->a.FrameByFrameMax)
//		{
//			animation->a.FrameByFrameCnt++;
//		}
//		else
//		{
//			//コマを進めている部分
//			if (animation->a.NowHandleIndex < animation->a.DivX * animation->a.DivY - 1)
//			{
//				animation->a.NowHandleIndex++;
//			}
//			else
//			{
//				animation->a.NowHandleIndex = 0;
//			}
//
//			//アニメーションの要素数をセット
//			animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];
//
//			//コマ送り初期化
//			animation->a.FrameCnt++;
//		}
//
//		//アニメーションが無限継続ではないとき
//		if (animation->a.FrameMax != AnimationInfinity)
//		{
//			//アニメーションが1回のみならアニメーション時間を無視
//			if (animation->a.FrameMax != AnimationOnce)
//			{
//				//アニメーション時間が終わりならばアニメーション終了
//				if (animation->a.FrameCnt > animation->a.FrameMax)
//				{
//					animation->a.IsAnimStartFlg = FALSE;    //アニメーション開始フラグOFF
//					animation->g.c.IsDraw = FALSE;          //アニメーション開始フラグOFF
//				}
//			}
//
//			//アニメーションのコマの最後ならばアニメーション終了
//			if (animation->a.NowHandleIndex >= animation->a.DivX * animation->a.DivY - 1)
//			{
//				animation->a.IsAnimStartFlg = FALSE;    //アニメーション開始フラグOFF
//				animation->g.c.IsDraw = FALSE;          //アニメーション開始フラグOFF
//			}
//		}
//			
//	}
//
//	return;
//}
//
////解放
//VOID DeleteAnimation(Animation animation)
//{
//	//正常に読み込みができていれば
//	if (animation.Handle != NULL && animation.Handle[0] != -1)
//	{
//		//メモリから解放
//		for (int i = 0; i < animation.a.DivX * animation.a.DivY; i++)
//		{
//			DeleteGraph(animation.Handle[i]);
//		}
//
//		//動的確保したメモリも解放
//		free(animation.Handle);
//	}
//
//	//2回以上のfreeを防ぎプログラムのクラッシュ防止
//	animation.Handle = NULL;
//
//	return;
//}
//
////アニメーション開始
//void AnimationStart(Animation* animation, int MillTime, int MillInterval)
//{
//	//アニメーションの秒数を初期化
//	animation->a.FrameCnt = 0;
//
//	//アニメーションの継続時間を計算
//	if (MillTime == AnimationInfinity)
//	{
//		//もしアニメーションが無限継続なら、実際のMAX時間を計算させない
//		animation->a.FrameMax = AnimationInfinity;
//	}
//	else if (MillTime == AnimationOnce)
//	{
//		//もしアニメーションが1回のみなら、実際のMAX時間を計算させない
//		animation->a.FrameMax = AnimationOnce;
//	}
//	else
//	{
//		animation->a.FrameMax = (MillTime / 1000.0f);
//	}
//
//	//アニメーションの間隔を初期化
//	animation->a.FrameByFrameCnt = 0;
//	animation->a.FrameByFrameMax = (MillInterval / 1000.0f);
//
//	//ハンドルの要素数も初期化
//	animation->a.NowHandleIndex = 0;
//
//	//最初のアニメーションの要素数をセット
//	animation->g.Handle = animation->Handle[animation->a.NowHandleIndex];
//
//	//アニメーション開始フラグON
//	animation->a.IsAnimStartFlg = TRUE;
//
//	//アニメーション描画フラグON
//	animation->g.c.IsDraw = TRUE;
//
//	return;
//}