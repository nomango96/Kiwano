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

#include "Image.h"
#include "../base/logs.h"
#include "../renderer/render.h"
#include "../platform/modules.h"

namespace kiwano
{
	Image::Image()
		: bitmap_(nullptr)
		, crop_rect_()
	{
	}

	Image::Image(Resource const& res)
		: Image()
	{
		this->Load(res);
	}

	Image::Image(Resource const& res, Rect const& crop_rect)
		: Image()
	{
		this->Load(res);
		this->Crop(crop_rect);
	}

	Image::Image(ComPtr<ID2D1Bitmap> const & bitmap)
		: Image()
	{
		SetBitmap(bitmap);
	}

	Image::~Image()
	{
	}

	bool Image::Load(Resource const& res)
	{
		HRESULT hr = S_OK;
		ComPtr<ID2D1Bitmap> bitmap;

		if (res.IsFileType())
		{
			if (!modules::Shlwapi::Get().PathFileExistsW(res.GetFileName().c_str()))
			{
				KGE_WARNING_LOG(L"Image file '%s' not found!", res.GetFileName().c_str());
				return false;
			}
			hr = Renderer::Instance().GetDeviceResources()->CreateBitmapFromFile(bitmap, res.GetFileName());
		}
		else
		{
			hr = Renderer::Instance().GetDeviceResources()->CreateBitmapFromResource(bitmap, res);
		}

		if (FAILED(hr))
		{
			KGE_ERROR_LOG(L"Load image file failed with HRESULT of %08X", hr);
			return false;
		}

		SetBitmap(bitmap);
		return true;
	}

	bool Image::IsValid() const
	{
		return !!bitmap_;
	}

	void Image::Crop(Rect const& crop_rect)
	{
		if (bitmap_)
		{
			auto bitmap_size = bitmap_->GetSize();
			crop_rect_.origin.x = std::min(std::max(crop_rect.origin.x, 0.f), bitmap_size.width);
			crop_rect_.origin.y = std::min(std::max(crop_rect.origin.y, 0.f), bitmap_size.height);
			crop_rect_.size.x = std::min(std::max(crop_rect.size.x, 0.f), bitmap_size.width - crop_rect.origin.x);
			crop_rect_.size.y = std::min(std::max(crop_rect.size.y, 0.f), bitmap_size.height - crop_rect.origin.y);
		}
	}

	float Image::GetWidth() const
	{
		return crop_rect_.size.x;
	}

	float Image::GetHeight() const
	{
		return crop_rect_.size.y;
	}

	Size Image::GetSize() const
	{
		return crop_rect_.size;
	}

	float Image::GetSourceWidth() const
	{
		if (bitmap_)
		{
			return bitmap_->GetSize().width;
		}
		return 0;
	}

	float Image::GetSourceHeight() const
	{
		if (bitmap_)
		{
			return bitmap_->GetSize().height;
		}
		return 0;
	}

	Size Image::GetSourceSize() const
	{
		if (bitmap_)
		{
			auto bitmap_size = bitmap_->GetSize();
			return Size{ bitmap_size.width, bitmap_size.height };
		}
		return Size{};
	}

	float Image::GetCropX() const
	{
		return crop_rect_.origin.x;
	}

	float Image::GetCropY() const
	{
		return crop_rect_.origin.y;
	}

	Point Image::GetCropPos() const
	{
		return crop_rect_.origin;
	}

	Rect Image::GetCropRect() const
	{
		return crop_rect_;
	}

	ComPtr<ID2D1Bitmap> const& Image::GetBitmap() const
	{
		return bitmap_;
	}

	void Image::SetBitmap(ComPtr<ID2D1Bitmap> const & bitmap)
	{
		if (bitmap)
		{
			bitmap_ = bitmap;
			crop_rect_.origin.x = crop_rect_.origin.y = 0;
			crop_rect_.size.x = bitmap_->GetSize().width;
			crop_rect_.size.y = bitmap_->GetSize().height;
		}
	}

}