#include "DxLib.h"
#include "Application.h"
#include"SceneMain.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	Application& application = Application::GetInstance();

	if (!application.Init())
	{
		return -1;// ���̃A�v���͕s���I�����܂����B
	}
	application.Run();

	return 0;
}