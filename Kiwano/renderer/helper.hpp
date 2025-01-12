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
#include "../common/ComPtr.hpp"
#include "../math/helper.h"
#include "../2d/Color.h"
#include <d2d1.h>

namespace kiwano
{
	namespace DX
	{
		template <typename T>
		inline void SafeRelease(T*& ptr)
		{
			if (ptr != nullptr)
			{
				ptr->Release();
				ptr = nullptr;
			}
		}

		inline D2D1_POINT_2F const& ConvertToPoint2F(Vec2 const& point)
		{
			return reinterpret_cast<D2D1_POINT_2F const&>(point);
		}

		inline D2D1_SIZE_F const& ConvertToSizeF(Vec2 const& size)
		{
			return reinterpret_cast<D2D1_SIZE_F const&>(size);
		}

		inline D2D1_RECT_F ConvertToRectF(Rect const& rect)
		{
			return D2D1_RECT_F{ rect.origin.x, rect.origin.y, rect.origin.x + rect.size.x, rect.origin.y + rect.size.y };
		}

		inline D2D1_COLOR_F const& ConvertToColorF(Color const& color)
		{
			return reinterpret_cast<D2D1_COLOR_F const&>(color);
		}

		inline D2D1_MATRIX_3X2_F const& ConvertToMatrix3x2F(Matrix const& matrix)
		{
			return reinterpret_cast<D2D1_MATRIX_3X2_F const&>(matrix);
		}

		// Converts a length in device-independent pixels (DIPs) to a length in physical pixels.
		inline float ConvertDipsToPixels(float dips, float dpi)
		{
			static const float dips_per_inch = 96.0f;
			return math::Floor(dips * dpi / dips_per_inch + 0.5f); // Round to nearest integer.
		}
	}
}
