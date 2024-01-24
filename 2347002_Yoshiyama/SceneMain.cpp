//�V�[�������̃\�[�X�t�@�C��

//�w�b�_�t�@�C���̓ǂݍ���
#include<DxLib.h>
#include<cassert>
#include "Pad.h"
#include "Rect.h"

#include "SceneMain.h"

#include "GamePart.h"


#include "Game.h"
//���̃t�@�C���ł����g���Ȃ��ϐ��@using namespace std;
namespace
{
	//��ʂ����C�v����̂ɂ�����t���[����
	constexpr int kWipeFrame = 30;
}
//�R���X�g���N�^
SceneMain::SceneMain():
	m_shakeFrame(0),
	m_wipeFrame(0)
{
	//�Q�[����ʕ`���̐���
	//��ʃT�C�Y�Ɠ����傫���̃O���t�B�b�N�f�[�^�𐶐�����
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//�O���t�B�b�N�̃��[�h
	m_GamePartHandle = LoadGraph("data/Player.png");
	assert(m_GamePartHandle != -1);
	m_enemyHandle = LoadGraph("data/Enemy.png");
	assert(m_enemyHandle != -1);
	m_bgHandle = LoadGraph("data/Map.png");
	assert(m_bgHandle != -1);
	m_wallHandle = LoadGraph("data/Wall.png");
	assert(m_wallHandle != -1);

	//�v���C���[�������̊m��
	m_pgamePart = new Gamepart;
	



	//�G�̏���
	//m_pEnemy(vector�������Ȃ���΃T�C�Y��0)
	

	//resize�֐���kEnemyMax�����f�[�^��ۑ��ł���悤�ɂ���
	
}
//�f�X�g���N�^
SceneMain::~SceneMain()
{
	//MakeScreen�Ő��������O���t�B�b�N���폜����
	DeleteGraph(m_gameScreenHandle);

	//�������폜
	DeleteGraph(m_GamePartHandle);
	DeleteGraph(m_enemyHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_wallHandle);

	//�v���C���[�̃������J��
	delete m_pgamePart;
	m_pgamePart = nullptr;
	

	//�w�i�̃������J��
	delete m_pBg;
	m_pBg = nullptr;

	//���������m�ۂ���Ă���G��T���ĊJ�����Ă���
}
//����������
void SceneMain::Init()
{
	assert(m_pgamePart);//m_pPlayer == nullptr�̏ꍇ�Ƃ܂�

	m_pgamePart->Init();
}
//�I������
void SceneMain::End()
{
}
//�X�V����
void SceneMain::Update()
{
	m_pgamePart->Update();



	////��ʗh��̃t���[���J�E���g�_�E��
	//m_wipeFrame--;
}
//�`�揈��
void SceneMain::Draw() const
{

	//�`���X�N���[�����N���A����
	///ClearDrawScreen();

	m_pgamePart->Draw();

	//�f�o�b�N�\��
	DrawString(8, 8, "SceneMain", 0xffffff);

	
	
}
//�߂��̓G�̍��W���擾���鏈��
Vec2 SceneMain::GetNearEemyPos(Vec2 pos) const
{
	//�G�����Ȃ��ꍇ�͓K���ȍ��W��Ԃ�
	Vec2 result{ 0,0 };
	//�ŏ��̓G�`�F�b�N�ς݃t���O
	bool isFirst = true;

	clsDx();
	//��ԋ߂��G�L�����N�^�[�̍��W��result�ɓ����
	///for(const auto& enemy : m_pEmemy)

	//���ׂĂ̓G�̃`�F�b�N���s�����̂ł�������ʂŊm��
	return result;
}



void SceneMain::CreateEnemyToPlayer()
{
}
