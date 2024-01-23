#pragma once
class Map
{
public:
	void Draw();
	void Update();
	void Init();

	void BackGround();
	
	//地面描画位置
	int GroundX=0;//320
	int GroundY=400;//540

	
private:
	

	//切り抜く場所
	int CropX=0;
	int CropY=128;

	//マップ表示サイズ
	int MapIndicationX = 256;
	int MapIndicationY = 160;




};

