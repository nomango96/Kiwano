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

#include "TimerManager.h"
#include "../base/logs.h"

namespace kiwano
{
	void TimerManager::UpdateTimers(Duration dt)
	{
		if (timers_.IsEmpty())
			return;

		TimerPtr next;
		for (auto timer = timers_.First(); timer; timer = next)
		{
			next = timer->NextItem();

			bool remove_after_update = false;
			timer->Update(dt, remove_after_update);

			if (remove_after_update)
				timers_.Remove(timer);
		}
	}

	void TimerManager::AddTimer(TimerPtr timer)
	{
		KGE_ASSERT(timer && "AddTimer failed, NULL pointer exception");

		if (timer)
		{
			timer->Reset();
			timers_.PushBack(timer);
		}
	}

	void TimerManager::StopTimers(String const& name)
	{
		if (timers_.IsEmpty())
			return;

		for (auto timer = timers_.First().Get(); timer; timer = timer->NextItem().Get())
		{
			if (timer->IsName(name))
			{
				timer->Stop();
			}
		}
	}

	void TimerManager::StartTimers(String const& name)
	{
		if (timers_.IsEmpty())
			return;
		
		for (auto timer = timers_.First().Get(); timer; timer = timer->NextItem().Get())
		{
			if (timer->IsName(name))
			{
				timer->Start();
			}
		}
	}

	void TimerManager::RemoveTimers(String const& name)
	{
		if (timers_.IsEmpty())
			return;

		TimerPtr next;
		for (auto timer = timers_.First(); timer; timer = next)
		{
			next = timer->NextItem();
			if (timer->IsName(name))
			{
				timers_.Remove(timer);
			}
		}
	}

	void TimerManager::StopAllTimers()
	{
		if (timers_.IsEmpty())
			return;

		for (auto timer = timers_.First().Get(); timer; timer = timer->NextItem().Get())
		{
			timer->Stop();
		}
	}

	void TimerManager::StartAllTimers()
	{
		if (timers_.IsEmpty())
			return;

		for (auto timer = timers_.First().Get(); timer; timer = timer->NextItem().Get())
		{
			timer->Start();
		}
	}

	void TimerManager::RemoveAllTimers()
	{
		timers_.Clear();
	}

	const TimerManager::Timers & TimerManager::GetAllTimers() const
	{
		return timers_;
	}
}
