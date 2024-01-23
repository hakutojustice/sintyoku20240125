//�Q�[���V�[���̃w�b�_�t�@�C��
#pragma once
//�w�b�_�t�@�C���̓ǂݍ���
#include "GameCommon.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "MyGameLib.h"
#include "Player.h"

//�N���X�̓ǂݍ���
class SceneMain;
class Player;

class GameScene
{
private:
	//�����o�ϐ�
	SceneKind _nextScene,_tempScene;//�V�[���X�V�p
	SceneMain* m_pSceneMain;
	Player* m_player;


public:
	/*�R���X�g���N�^*/
	GameScene() :
		_nextScene(SceneKind::GAMESCENE),
		_tempScene(SceneKind::GAMESCENE)
	{
		//�V�[���̃������̊m��
		m_pSceneMain = new SceneMain;
	};
	//�f�X�g���N�^
	~GameScene()
	{
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
	}
	SceneKind Update()
	{
		m_pSceneMain->Update();
		/*�V�[���@�ۏ���*/
		if (MyKeyInput::isDownKey(KEY_INPUT_RETURN))
		{
			_nextScene = SceneKind::TITLESCENE;
		}
		//�G�Ɠ������Ă�����^�C�g����ʂɂ��鏈���ɍ�����s���Ă���
		

		return _nextScene;
	}
	void Draw()
	{
		//���݂̃V�[������`��
		DrawString(8, 8, "SceneName:GameScene", GetColor(255, 255, 255));
		m_pSceneMain->Draw();
	}
	void Init()
	{
		//�����o�ϐ��̏�����
		_nextScene = SceneKind::GAMESCENE;
		_tempScene = SceneKind::GAMESCENE;
		m_pSceneMain->Init();
	}
};
