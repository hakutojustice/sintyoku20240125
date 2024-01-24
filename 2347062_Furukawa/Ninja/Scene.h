#pragma once

class Input;
class SceneManager;

//�V�[�����N���X
//�����ȃV�[���̊�ɂȂ�N���X

class Scene
{
public:

	//��������SceneManager�̎Q�Ƃ��󂯎���Ă���
	
	//SceneManager�̎Q��
	Scene(SceneManager& manager);

	//�V�[���̍X�V
	//���̓I�u�W�F�N�g
	virtual void Update(Input& input) = 0;
	virtual void Draw() = 0;
private:
	SceneManager& manager_;
};

