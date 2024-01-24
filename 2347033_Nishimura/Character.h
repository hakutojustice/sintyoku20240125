#pragma once
#include "Map.h"
#include "SceneManager.h"
#include "DxLib.h"
class Map;
class Enemy;
class Character
{
public:
	 Character();
	~Character();

	void Init();
	void Draw();
	void Move(Map& gamescene);
    void Update();
	void Collision(Enemy&cEnemy);
	void FallCollision();
	int gpUpdateKey();
	
	//プレイヤーの初期位置
   //キャラの最初のポジション 
	int Player_posX = 0;
	int Player_posY = 300;
	
	int PlayerHandle=LoadGraph("Cockroach.png");


private:

	


  //キャラ移動スピード
	int CharaMoveSpeed=5;
	//キャラジャンプフラグ
	bool JumpFlag;
	
	//キャラの初速度
	int JumpInitialVelocity=10;
	//キャラにかかる重力処理の値
	float Jumpgravity=2.5f;
	//キャラのジャンプスピード
	int JumpSpeed = 50;
	//ジャンプ1秒当たりのフレーム
	int JumpFlame;
	//キャラ座標の保存
	int preservationY;

	//キャラ1マス分の大きさ
	int PlayerChipSizeX=32;
	int PlayerChipSizeY=32;


	//キャラ切り抜きサイズ
	int PlayerWidthX=32;
	int PlayerHeightY=32;






};



