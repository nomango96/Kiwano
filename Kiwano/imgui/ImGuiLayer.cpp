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

#include "../kiwano-imgui.h"

namespace kiwano
{
	namespace
	{
		Map<int, int> mouse_buttons = 
		{
			{ MouseButton::Left, 0 },
			{ MouseButton::Right, 1 },
			{ MouseButton::Middle, 2 }
		};
	}

	ImGuiLayer::ImGuiLayer()
	{
		target_window_ = Renderer::Instance().GetTargetWindow();
		SetSwallowEvents(true);
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ImGuiView::Instance().RemoveLayer(this);
	}

	void ImGuiLayer::OnMouseButtonDown(int btn, Point const & p)
	{
		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == nullptr)
			::SetCapture(target_window_);

		KGE_ASSERT(mouse_buttons.find(btn) != mouse_buttons.end());
		ImGui::GetIO().MouseDown[mouse_buttons[btn]] = true;
	}

	void ImGuiLayer::OnMouseButtonUp(int btn, Point const & p)
	{
		KGE_ASSERT(mouse_buttons.find(btn) != mouse_buttons.end());
		ImGui::GetIO().MouseDown[mouse_buttons[btn]] = false;

		if (!ImGui::IsAnyMouseDown() && ::GetCapture() == target_window_)
			::ReleaseCapture();
	}

	void ImGuiLayer::OnMouseWheel(float wheel)
	{
		ImGui::GetIO().MouseWheel += wheel;
	}

	void ImGuiLayer::OnKeyDown(int key)
	{
		KGE_ASSERT(key < 256);
		ImGui::GetIO().KeysDown[key] = 1;
	}

	void ImGuiLayer::OnKeyUp(int key)
	{
		KGE_ASSERT(key < 256);
		ImGui::GetIO().KeysDown[key] = 0;
	}

	void ImGuiLayer::OnChar(char c)
	{
		ImGui::GetIO().AddInputCharacter(c);
	}

	void ImGuiLayer::OnUpdate(Duration dt)
	{
		ImGuiIO& io = ImGui::GetIO();

		// Setup time step
		io.DeltaTime = dt.Seconds();

		// Read keyboard modifiers inputs
		io.KeyCtrl = Input::Instance().IsDown(KeyCode::Ctrl);
		io.KeyShift = Input::Instance().IsDown(KeyCode::Shift);
		io.KeyAlt = Input::Instance().IsDown(KeyCode::Alt);
		io.KeySuper = false;
		// io.KeysDown[], io.MousePos, io.MouseDown[], io.MouseWheel: filled by the WndProc handler below.

		// Update OS mouse position
		UpdateMousePos();

		// Update OS mouse cursor with the cursor requested by imgui
		UpdateMouseCursor();
	}

	void ImGuiLayer::OnRender()
	{
		ImGuiView::Instance().NewFrame();

		for (const auto& pipeline : pipelines_)
		{
			pipeline.second();
		}

		ImGuiView::Instance().Render();
	}

	void ImGuiLayer::UpdateMousePos()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Set OS mouse position if requested (rarely used, only when ImGuiConfigFlags_NavEnableSetMousePos is enabled by user)
		if (io.WantSetMousePos)
		{
			POINT pos = { (int)io.MousePos.x, (int)io.MousePos.y };
			HWND hwnd = target_window_;
			::ClientToScreen(hwnd, &pos);
			::SetCursorPos(pos.x, pos.y);
		}

		Point pos = Input::Instance().GetMousePos();
		io.MousePos = ImVec2(pos.x, pos.y);
	}

	void ImGuiLayer::UpdateMouseCursor()
	{
		static ImGuiMouseCursor last_mouse_cursor = ImGuiMouseCursor_COUNT;

		ImGuiMouseCursor imgui_cursor = ImGui::GetMouseCursor();

		if (last_mouse_cursor != imgui_cursor)
		{
			last_mouse_cursor = imgui_cursor;

			if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
				return;

			MouseCursor cursor = MouseCursor::Arrow;
			switch (imgui_cursor)
			{
			case ImGuiMouseCursor_Arrow:        cursor = MouseCursor::Arrow; break;
			case ImGuiMouseCursor_TextInput:    cursor = MouseCursor::TextInput; break;
			case ImGuiMouseCursor_ResizeAll:    cursor = MouseCursor::SizeAll; break;
			case ImGuiMouseCursor_ResizeEW:     cursor = MouseCursor::SizeWE; break;
			case ImGuiMouseCursor_ResizeNS:     cursor = MouseCursor::SizeNS; break;
			case ImGuiMouseCursor_ResizeNESW:   cursor = MouseCursor::SizeNESW; break;
			case ImGuiMouseCursor_ResizeNWSE:   cursor = MouseCursor::SizeNWSE; break;
			case ImGuiMouseCursor_Hand:         cursor = MouseCursor::Hand; break;
			}

			GetScene()->SetMouseCursor(cursor);
		}
	}

	void ImGuiLayer::AddItem(ImGuiPipeline const & item, String const & name)
	{
		pipelines_.insert(std::make_pair(name, item));
	}

	void ImGuiLayer::RemoveItem(String const & name)
	{
		auto iter = pipelines_.find(name);
		if (iter != pipelines_.end())
		{
			pipelines_.erase(iter);
		}
	}

	void ImGuiLayer::RemoveAllItems()
	{
		pipelines_.clear();
	}

}