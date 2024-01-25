#include "SceneManager.h"
#include "TitleScene.h"
#include "Map.h"
#include "OptionScene.h"
#include "Text.h"
#include <memory>
class Map;
class TitleScene;
class OptionScene;
class Text;

OptionScene* game_option;
Map* gm_scene;
TitleScene* m_title;



SceneManager::SceneManager()
{
	

}

SceneManager::~SceneManager()
{


}

void SceneManager::ChangeScene(Scene scene)
{
	
	switch (scene)
	{
	case SceneManager::Title:
		m_title = new TitleScene;
		break;
	case SceneManager::S_Option:
		game_option = new OptionScene;
		break;
	case SceneManager::Playing:
		gm_scene = new Map;
		break;
	case SceneManager::End:
		false;
		break;
	default:
		break;
	}
}

void SceneManager::SceneUpdate()
{

}

void SceneManager::SceneDraw()
{
}
