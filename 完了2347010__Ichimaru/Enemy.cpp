#include "DxLib.h"
#include "Enemy.h"
#include "Haikei.h"
#include "game.h"
#include "key.h"
#include "Player.h"

void InitializeEnemy(Enemy& enemy)
{
    enemy.Graph = LoadGraph("data/Enemy.png");
    enemy.Graph2 = LoadGraph("data/Enemy2.png");
    enemy.Graph3 = LoadGraph("data/Enemy3.png");    
    //enemy.Graph4 = LoadGraph("data/Enemy4s.png");

    enemy.R = enemy.Graph;
    enemy.R2 = enemy.Graph2;
    enemy.R3 = enemy.Graph3;
   // enemy.R4 = enemy.Graph4;
  
}

void UpdateEnemy(Enemy& enemy)
{
    if (enemy.moveX > 1600)
    {
        enemy.moveX = 0;

    }
                    
    if (enemy.moveX2 < -10)
    {
        enemy.moveX2 = 1600;

    }


    if (enemy.moveX3 > 1600)
    {
        enemy.moveX3 = 0;

    }


    /*if (enemy.moveX4 > 1600)
    {
        enemy.moveX4 = 0;

    }*/
}

void DrawEnemy(Enemy& enemy)
{
    enemy.moveX += 13;
  
    enemy.moveX2 -= 15;

    enemy.moveX3 += 10;

   // enemy.moveX4 += 20;
    

    //“G1‚Ì“®‚«
    if (enemy.z < 30)
    {
        DrawGraph(enemy.moveX, enemy.y, enemy.R, TRUE);
    }
    else if (enemy.z > 30)
    {
        DrawGraph(enemy.moveX, enemy.y, enemy.R2, TRUE);
    }
   
    //“G2‚Ì“®‚«
    if (enemy.z2 < 30)
    {
        DrawGraph(enemy.moveX2, enemy.y2, enemy.R, TRUE);
    }
    else if (enemy.z2 > 30)
    {
        DrawGraph(enemy.moveX2, enemy.y2, enemy.R2, TRUE);
    }

    //“G3‚Ì“®‚«
    if (enemy.z3 < 30)
    {
        DrawGraph(enemy.moveX3, enemy.y3, enemy.R, TRUE);
    }
    else if (enemy.z3 > 30)
    {
        DrawGraph(enemy.moveX3, enemy.y3, enemy.R3, TRUE);
    }

    
    ////“G4‚ÌoŒ»
    //if (player.Score > 10000)
    //{


    //    if (enemy.z4 < 30)
    //    {
    //        DrawGraph(enemy.moveX4, enemy.y4, enemy.R, TRUE);
    //    }
    //    else if (enemy.z4 > 30)
    //    {
    //        DrawGraph(enemy.moveX4, enemy.y4, enemy.R4, TRUE);
    //    }
    //}
}

void DDrawBox(Enemy& enemy)//Enemy‚ÌBOX
{

}

    
void UpdateBox(Enemy& enemy)
{
    
}
