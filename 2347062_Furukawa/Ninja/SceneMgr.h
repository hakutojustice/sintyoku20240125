#pragma once
class Input;
class Scene;
//�e�V�[���̑J�ڂƂ��������R���g���[������N���X
class SceneMgr
{
public:
	//�����Ă���V�[����Update�֐����Ăяo��
	//���̓N���X
	void Upsate(Input& input);
	//�����Ă���V�[���̕`��Draw�֐����Ăяo��
	void Draw();
	//���ݎ��s���̃V�[���������Œ�`���ꂽ�V�[���ɐ؂�ւ���
	//���̃V�[��
	void ChangeScene(Scene* nextScene);

private:
	Scene* scene_=nullptr;

};

