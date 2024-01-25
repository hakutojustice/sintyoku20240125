#pragma once

//�A�v���P�[�V�����S�̂̊Ǘ�����N���X
//�V���O���g���N���X
class Application
{
public:
	//Application�̃V���O���g���C���X�^���X��Ԃ�
	//Application�C���X�^���X
	static Application& GeetInstance()
	{
		static Application instance;
		return instance;
	}
	bool Init();
	void Run();

private:
	Application();
	//�R�s�[&����̋֎~
	Application(const Application& app)=delete;
	void operator=(const Application& app)=delete;

	//�㏈�����s��
	void Terminate();
};

