//�V�[�������̃w�b�_�t�@�C��
#pragma once

//�N���X�̃v���g�^�C�v�錾
class SceneMain;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();

	void Update();
	void Draw() const;

	void ChangeScene();

private:
	SceneMain* m_pMain;
};

