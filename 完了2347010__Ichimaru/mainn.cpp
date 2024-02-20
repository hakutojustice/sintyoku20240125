#include "DxLib.h"
#include "Enemy.h"
#include "Haikei.h"
#include "game.h"
#include "key.h"
#include "Player.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeFont("HG行書体");
    // 一部の関数はDxLib_Init()の前に実行する必要がある
    SetGraphMode(1600, 900, 16);
    ChangeWindowMode(true);

    if (DxLib_Init() == -1)		// ＤＸライブラリ初期化理
    {
        return -1;			// エラーが起きたら直ちに終了
    }

    SetDrawScreen(DX_SCREEN_BACK);
    SetFontSize(30);


    Player player;
    Enemy enemy;
    Haikei haikei;
    InitializePlayer(player);
    InitializeHaikei(haikei);
    InitializeEnemy(enemy);
   
    //最初のシーンはタイトルから
    NowGameScene = TitleScene;

    KeyInit();

    TitleInit();


    GameScene lastGameScene;

   
    while (ProcessMessage() != -1)
    {
        // このフレームの開始時刻を覚えておく
        LONGLONG start = GetNowHiPerformanceCount();

        // 描画を行う前に画面をクリアする
        ClearDrawScreen();

        // 画面を初期化する
        ClearDrawScreen();

        // タイトルシーンかどうかで描画を切り替える
        if (NowGameScene == TitleScene) {
            // タイトルシーンの描画
            TitleDraw();
        }
        else if (NowGameScene == PlayScene) {
            // ゲームシーンの描画
            UpdateHaikei(haikei);
            DrawHaikei(haikei); 
            CheckCollision(player, enemy);
            UpdatePlayer(player, enemy);
            UpdatePlayer(player);
            UpdateBox(enemy);
            DDrawBox(enemy);
            DDrawBox(player);
            UpdateEnemy(enemy);
            DrawEnemy(enemy);
            DrawGraph(player.PlayerX, player.PlayerY, player.PlayerGraph, TRUE);    

            // スコア表示
            if (player.Dead == 0 || 1) 
            {
                DrawFormatString(1200, 450, GetColor(0, 255, 0),"Score: %d", player.Score);
                if (player.Score > 5000)
                {
                    DrawFormatString(1200, 450, GetColor(255, 0, 0), "Score: %d", player.Score);
                }

                if (player.Score > 10000)
                {
                    DrawFormatString(1200, 450, GetColor(255, 255, 0), "Score: %d", player.Score);
                }

            }

        }

        // キーボード更新
        KeyUpdate();

        // シーン切り替え
        switch (NowGameScene)
        {
        case TitleScene:
            if (TitleCtrl()) {

                continue;
            }
            else {
                break;
            }
        case PlayScene:
            if (lastGameScene == TitleScene) {
                //タイトルからゲームに移った瞬間
                player.PlayerX = 699;
                player.PlayerY = 699;
                player.Score = 0;
                player.Dead = 0;              
                enemy.moveX = 0;
                enemy.moveX2 = 0;
                enemy.moveX3 = 0;
               // enemy. moveX4 = 0;
                enemy.z = 0;
                enemy.z2 = 0;
                enemy.z3 = 0;
              //  enemy.z4 = 0;
                enemy.y = 699;
                enemy.y2 = 699;
                enemy.y3 = 699;
              // enemy.y4 = 699;
                
            }
           
           
            PlayCtrl();

            break;
        default:
            break;
        }
        lastGameScene = NowGameScene;

        // 画面が切り替わるのを待つ
        ScreenFlip();

        // escキーでゲーム終了
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        // FPS60に固定する
        while (GetNowHiPerformanceCount() - start < 16667)
        {
            // 16.66ミリ秒(16667マイクロ秒)経過するまで待つ
        }
    }
    // スコア表示
    DrawFormatString(10, 30, GetColor(255, 255, 255), "Score: %d", player.Score);
   
    DxLib_End();				// ＤＸライブラリ使用の終了処理

    return 0;				// ソフトの終了 
}
