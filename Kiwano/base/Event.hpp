// Copyright (c) 2016-2018 Kiwano - Nomango
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once
#include "keys.hpp"

namespace kiwano
{

	// 鼠标事件
	struct MouseEvent
	{
		float x;
		float y;
		bool left_btn_down;		// 左键是否按下
		bool right_btn_down;	// 右键是否按下

		union
		{
			struct	// Events::MouseDown | Events::MouseUp | Events::MouseClick
			{
				int button;
			};

			struct	// Events::MouseWheel
			{
				float wheel;
			};
		};

		static bool Check(UINT type);
	};

	// 键盘事件
	struct KeyboardEvent
	{
		int count;
		union
		{
			struct	// Events::KeyDown | Events::KeyUp
			{
				int code;		// enum KeyCode
			};

			struct	// Events::Char
			{
				char c;
			};
		};

		static bool Check(UINT type);
	};

	// 窗口事件
	struct WindowEvent
	{
		union
		{
			struct		// Events::WindowMoved
			{
				int x;
				int y;
			};

			struct		// Events::WindowResized
			{
				int width;
				int height;
			};

			struct		// Events::WindowFocusChanged
			{
				bool focus;
			};

			struct		// Events::WindowTitleChanged
			{
				const wchar_t* title;
			};
		};

		static bool Check(UINT type);
	};

	// 自定义事件
	struct CustomEvent
	{
		void* data;
	};

	class Node;

	// 事件
	struct KGE_API Event
	{
		enum Type : UINT
		{
			First,

			// 鼠标事件
			MouseFirst,
			MouseMove,			// 移动
			MouseBtnDown,		// 鼠标按下
			MouseBtnUp,			// 鼠标抬起
			MouseWheel,			// 滚轮滚动
			MouseHover,			// 鼠标移入
			MouseOut,			// 鼠标移出
			Click,				// 鼠标点击
			MouseLast,

			// 按键事件
			KeyFirst,
			KeyDown,			// 按键按下
			KeyUp,				// 按键抬起
			Char,				// 输出字符
			KeyLast,

			// 窗口消息
			WindowFirst,
			WindowMoved,		// 窗口移动
			WindowResized,		// 窗口大小变化
			WindowFocusChanged,	// 获得或失去焦点
			WindowTitleChanged,	// 标题变化
			WindowClosed,		// 窗口被关闭
			WindowLast,

			Last
		};

		UINT type;
		Node* target;

		union
		{
			MouseEvent mouse;
			KeyboardEvent key;
			WindowEvent win;
			CustomEvent custom;
		};

		Event(UINT type = Type::First) : type(type), target(nullptr) {}
	};


	// Check-functions

	inline bool MouseEvent::Check(UINT type)
	{
		return type > Event::MouseFirst && type < Event::MouseLast;
	}

	inline bool KeyboardEvent::Check(UINT type)
	{
		return type > Event::KeyFirst && type < Event::KeyLast;
	}

	inline bool WindowEvent::Check(UINT type)
	{
		return type > Event::WindowFirst && type < Event::WindowLast;
	}

}
