#pragma once
#include "e2dmacros.h"
#include "e2dcommon.h"
#include "e2dcustom.h"


// Base Classes

namespace e2d
{


// 游戏控制
class Game
{
public:
	// 获取游戏单例
	static Game * getInstance();

	// 初始化游戏
	bool init(
		const String& mutexName = L""	/* 进程互斥体名称 */
	);

	// 启动游戏
	void start(
		bool cleanup = true				/* 自动清理资源 */
	);

	// 暂停游戏
	void pause();

	// 继续游戏
	void resume();

	// 结束游戏
	void quit();

	// 清理资源
	void cleanup();

	// 销毁实例
	void destroy();

	// 重置游戏内部计时
	void reset();

	// 游戏是否暂停
	bool isPaused();

private:
	Game();

	E2D_DISABLE_COPY(Game);

private:
	bool	_ended;
	bool	_paused;
	bool	_initialized;
	static Game * _instance;
};


// 窗口控制
class Window
{
	friend class Game;

public:
	// 鼠标指针样式
	enum class Cursor : int
	{
		Normal,		/* 默认指针样式 */
		Hand,		/* 手状指针 */
		No,			/* 禁止指针 */
		Wait,		/* 沙漏指针 */
		ArrowWait	/* 默认指针和小沙漏 */
	};

public:
	// 修改窗口大小
	static void setSize(
		int width,			/* 窗口宽度 */
		int height			/* 窗口高度 */
	);

	// 设置窗口标题
	static void setTitle(
		const String& title	/* 窗口标题 */
	);

	// 设置窗口图标
	static void setIcon(
		int iconID
	);

	// 设置鼠标指针样式
	static void setCursor(
		Cursor cursor
	);

	// 获取窗口标题
	static String getTitle();

	// 获取窗口宽度
	static double getWidth();

	// 获取窗口高度
	static double getHeight();

	// 获取窗口大小
	static Size getSize();

	// 获取窗口句柄
	static HWND getHWnd();

	// 打开/隐藏控制台
	static void showConsole(
		bool show = true
	);

	// 是否允许响应输入法
	static void setTypewritingEnable(
		bool enable
	);

	// 弹出提示窗口
	static void info(
		const String& text,					/* 内容 */
		const String& title = L"Infomation"	/* 窗口标题 */
	);

	// 弹出警告窗口
	static void warning(
		const String& text,					/* 内容 */
		const String& title = L"Warning"	/* 窗口标题 */
	);

	// 弹出错误窗口
	static void error(
		const String& text,					/* 内容 */
		const String& title = L"Error"		/* 窗口标题 */
	);

private:
	// 初始化窗口
	static bool __init();

	// 重置窗口属性
	static void __uninit();

	// 处理窗口消息
	static void __poll();

	// Win32 窗口消息回调程序
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


// 时间控制
class Time
{
	friend class Game;

public:
	// 获取上一帧与当前帧的时间间隔（秒）
	static double getDeltaTime();

	// 获取上一帧与当前帧的时间间隔（毫秒）
	static unsigned int getDeltaTimeMilliseconds();

	// 获取游戏总时长（秒）
	static double getTotalTime();

	// 获取游戏总时长（毫秒）
	static unsigned int getTotalTimeMilliseconds();

private:
	// 初始化计时操作
	static bool __init();

	// 是否达到更新时间
	static bool __isReady();

	// 更新当前时间
	static void __updateNow();

	// 更新时间信息
	static void __updateLast();

	// 重置时间信息
	static void __reset();

	// 挂起线程
	static void __sleep();
};


class Listener;

// 输入控制
class Input
{
	friend class Game;

public:
	// 鼠标键值
	enum class Mouse : int
	{
		Left,		/* 鼠标左键 */
		Right,		/* 鼠标右键 */
		Middle		/* 鼠标中键 */
	};


	// 键盘键值
	enum class Key : int
	{
		Up = 0xC8,
		Left = 0xCB,
		Right = 0xCD,
		Down = 0xD0,
		Enter = 0x1C,
		Space = 0x39,
		Esc = 0x01,
		Q = 0x10,
		W = 0x11,
		E = 0x12,
		R = 0x13,
		T = 0x14,
		Y = 0x15,
		U = 0x16,
		I = 0x17,
		O = 0x18,
		P = 0x19,
		A = 0x1E,
		S = 0x1F,
		D = 0x20,
		F = 0x21,
		G = 0x22,
		H = 0x23,
		J = 0x24,
		K = 0x25,
		L = 0x26,
		Z = 0x2C,
		X = 0x2D,
		C = 0x2E,
		V = 0x2F,
		B = 0x30,
		N = 0x31,
		M = 0x32,
		Num1 = 0x02,
		Num2 = 0x03,
		Num3 = 0x04,
		Num4 = 0x05,
		Num5 = 0x06,
		Num6 = 0x07,
		Num7 = 0x08,
		Num8 = 0x09,
		Num9 = 0x0A,
		Num0 = 0x0B,
		Numpad7 = 0x47,
		Numpad8 = 0x48,
		Numpad9 = 0x49,
		Numpad4 = 0x4B,
		Numpad5 = 0x4C,
		Numpad6 = 0x4D,
		Numpad1 = 0x4F,
		Numpad2 = 0x50,
		Numpad3 = 0x51,
		Numpad0 = 0x52
	};

public:
	// 检测键盘某按键是否正被按下
	static bool isDown(
		Key key
	);

	// 检测键盘某按键是否被点击
	static bool isPress(
		Key key
	);

	// 检测键盘某按键是否正在松开
	static bool isRelease(
		Key key
	);

	// 检测鼠标按键是否正被按下
	static bool isDown(
		Mouse code
	);

	// 检测鼠标按键是否被点击
	static bool isPress(
		Mouse code
	);

	// 检测鼠标按键是否正在松开
	static bool isRelease(
		Mouse code
	);

	// 获得鼠标X轴坐标值
	static double getMouseX();

	// 获得鼠标Y轴坐标值
	static double getMouseY();

	// 获得鼠标坐标值
	static Point getMousePos();

	// 获得鼠标X轴坐标增量
	static double getMouseDeltaX();

	// 获得鼠标Y轴坐标增量
	static double getMouseDeltaY();

	// 获得鼠标Z轴（鼠标滚轮）坐标增量
	static double getMouseDeltaZ();

	// 添加输入监听
	static Listener * addListener(
		const Function& func,		/* 监听到用户输入时的执行函数 */
		const String& name = L"",	/* 监听器名称 */
		bool paused = false			/* 是否暂停 */
	);

	// 添加碰撞监听
	static void addListener(
		Listener * listener			/* 监听器 */
	);

	// 移除监听器
	static void removeListener(
		Listener * listener			/* 监听器 */
	);

	// 启动输入监听
	static void startListener(
		const String& name
	);

	// 停止输入监听
	static void stopListener(
		const String& name
	);

	// 移除输入监听
	static void removeListener(
		const String& name
	);

	// 启动所有监听器
	static void startAllListeners();

	// 停止所有监听器
	static void stopAllListeners();

	// 移除所有监听器
	static void removeAllListeners();

private:
	// 初始化 DirectInput 以及键盘鼠标设备
	static bool __init();

	// 刷新输入信息
	static void __update();

	// 刷新设备状态
	static void __updateDeviceState();

	// 更新监听器
	static void __updateListeners();

	// 卸载 DirectInput
	static void __uninit();

	// 清空监听器
	static void __clearListeners();
};


// 渲染器
class Renderer
{
	friend class Game;
	friend class Window;

public:
	// 获取背景色
	static Color getBackgroundColor();

	// 修改背景色
	static void setBackgroundColor(
		Color color
	);

	// 显示 FPS
	static void showFps(
		bool show = true
	);

	// 获取系统 DPI 缩放
	static float getDpiScaleX();

	// 获取系统 DPI 缩放
	static float getDpiScaleY();

	// 获取 ID2D1Factory 对象
	static ID2D1Factory * getID2D1Factory();

	// 获取 ID2D1HwndRenderTarget 对象
	static ID2D1HwndRenderTarget * getRenderTarget();

	// 获取 ID2D1SolidColorBrush 对象
	static ID2D1SolidColorBrush * getSolidColorBrush();

	// 获取 IWICImagingFactory 对象
	static IWICImagingFactory * getIWICImagingFactory();

	// 获取 IDWriteFactory 对象
	static IDWriteFactory * getIDWriteFactory();

	// 获取文字渲染器
	static TextRenderer * getTextRenderer();

	// 获取 Miter 样式的 ID2D1StrokeStyle
	static ID2D1StrokeStyle * getMiterID2D1StrokeStyle();

	// 获取 Bevel 样式的 ID2D1StrokeStyle
	static ID2D1StrokeStyle * getBevelID2D1StrokeStyle();

	// 获取 Round 样式的 ID2D1StrokeStyle
	static ID2D1StrokeStyle * getRoundID2D1StrokeStyle();

private:
	// 渲染游戏画面
	static void __render();

	// 创建设备无关资源
	static bool __createDeviceIndependentResources();

	// 创建设备相关资源
	static bool __createDeviceResources();

	// 删除设备相关资源
	static void __discardDeviceResources();

	// 删除所有渲染相关资源
	static void __discardResources();
};


// 垃圾回收装置
class GC
{
	friend class Game;
	friend class Object;

public:
	// 保留对象
	template <typename Type>
	static inline void retain(Type*& p)
	{
		if (p != nullptr)
		{
			p->retain();
		}
	}

	// 释放对象
	template <typename Type>
	static inline void release(Type*& p)
	{
		if (p != nullptr)
		{
			p->release();
			p = nullptr;
		}
	}

	// 通知 GC 回收垃圾内存
	static void notify();

	// 手动回收垃圾内存
	static void flush();

private:
	// 将对象放入 GC
	static void __add(
		Object * pObject
	);

	// 更新 GC
	static void __update();

	// 清空所有对象
	static void __clear();
};

}