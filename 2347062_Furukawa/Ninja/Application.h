#pragma once

//アプリケーション全体の管理するクラス
//シングルトンクラス
class Application
{
public:
	//Applicationのシングルトンインスタンスを返す
	//Applicationインスタンス
	static Application& GeetInstance()
	{
		static Application instance;
		return instance;
	}
	bool Init();
	void Run();

private:
	Application();
	//コピー&代入の禁止
	Application(const Application& app)=delete;
	void operator=(const Application& app)=delete;

	//後処理を行う
	void Terminate();
};

