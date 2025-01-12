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
#include "Action.h"

namespace kiwano
{
	class KGE_API ActionManager
	{
		using Actions = IntrusiveList<ActionPtr>;

	public:
		// 添加动作
		ActionPtr AddAction(
			ActionPtr action
		);

		// 获取动作
		ActionPtr GetAction(
			String const& name
		);

		// 继续所有暂停动作
		void ResumeAllActions();

		// 暂停所有动作
		void PauseAllActions();

		// 停止所有动作
		void StopAllActions();

		// 获取所有动作
		Actions const& GetAllActions() const;

	protected:
		void UpdateActions(NodePtr target, Duration dt);

	protected:
		Actions actions_;
	};
}
