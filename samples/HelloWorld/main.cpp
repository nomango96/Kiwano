// Copyright (C) 2019 Nomango

#include "kiwano.h"

using namespace kiwano;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class MainScene
	: public Scene
{
public:
	MainScene()
	{
		// 创建文字节点
		TextPtr text = new Text(L"Hello Kiwano!");
		// 设置节点大小为文字布局大小
		text->SetSize(text->GetLayoutSize());
		// 修改节点位置, 使节点在屏幕上居中
		text->SetPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		// 修改节点锚点, 使文字中心对齐屏幕中心
		text->SetAnchor(0.5, 0.5);
		// 添加到场景中
		this->AddChild(text);
	}
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	try
	{
		// 创建 Kiwano 程序实例
		Application app;

		// 创建初始化选项
		Options options;
		// 设置窗口宽高
		options.width = WINDOW_WIDTH;
		options.height = WINDOW_HEIGHT;
		// 初始化 app
		app.Init(options);

		// 创建场景并进入
		ScenePtr scene = new MainScene;
		app.EnterScene(scene);

		// 运行
		app.Run();
	}
	catch (std::exception& e)
	{
		::MessageBoxA(nullptr, e.what(), "An exception has occurred!", MB_ICONERROR | MB_OK);
	}
	return 0;
}
