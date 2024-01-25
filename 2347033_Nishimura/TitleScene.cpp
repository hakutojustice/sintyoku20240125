#include "TitleScene.h"
#include "BaseNumber.h"
#include "Dxlib.h"
#include "SceneManager.h"
bool TitleScene::Update()
{
	/*タイトルシーンの処理*/
	//矢印の描画
	MakeSelectTriangle();
	//Key入力
	gpUpdateKey();
    

	if (MenuElement->y == 340 && titleP.Key[KEY_INPUT_SPACE])
	{
		SceneManager::Scene::S_Option;
	

	}
	
	if (titleP.Key[KEY_INPUT_DOWN])
	{
		
		triangle.y1 = 345;
		triangle.y2 = 330;
		triangle.y3 = 370;

	}
	
	if (titleP.Key[KEY_INPUT_UP])
	{
		triangle.y1 = 305;
		triangle.y2 = 290;
		triangle.y3 = 330;
	}
	if ((titleP.Key[KEY_INPUT_Z] == 1) || (titleP.Key[KEY_INPUT_RETURN] == 1)) {

		return false;//シーン切り替え
	}
	//メニューの描画
	for (int i = 0; i < 50; i++) {		//メニュー項目を描画
	
		
		ChangeFont("Super Mario 256");
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 0xffffff, MenuElement[i].name);
	}

	//正常終了
	return true;//シーンを切り替えない
}

int TitleScene::gpUpdateKey() {
	char tmpkey[256]; //現在のキー入力状態を格納する
	GetHitKeyStateAll(tmpkey); //すべてのキー入力状態を得る
	for (int i = 0; i < 256; i++) {	//i番のキーコードに対応するキーが押されていたら
		if (tmpkey[i] != 0) {
			titleP.Key[i]++;				//加算
		}
		else {						//押されていなければ
		   titleP.Key[i] = 0;
		}

	}
	return 0;
}

void TitleScene::MakeSelectTriangle()
{

	DrawTriangle(triangle.x1,
		triangle.y1,
		triangle.x2,
		triangle.y2,
		triangle.x3,
		triangle.y3,
		0xffffff, true);

}