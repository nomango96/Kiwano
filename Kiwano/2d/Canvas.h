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
#include "Node.h"
#include "Font.hpp"
#include "TextStyle.hpp"
#include "../renderer/TextRenderer.h"

#undef DrawText

namespace kiwano
{
	// 画布
	class KGE_API Canvas
		: public VisualNode
	{
	public:
		Canvas();

		Canvas(
			Size const& size
		);

		Canvas(
			float width,
			float height
		);

		virtual ~Canvas();

		// 开始绘图
		void BeginDraw();

		// 结束绘图
		void EndDraw();

		// 画直线
		void DrawLine(
			const Point& begin,
			const Point& end
		);

		// 画圆形边框
		void DrawCircle(
			const Point& center,
			float radius
		);

		// 画椭圆形边框
		void DrawEllipse(
			const Point& center,
			float radius_x,
			float radius_y
		);

		// 画矩形边框
		void DrawRect(
			const Rect& rect
		);

		// 画圆角矩形边框
		void DrawRoundedRect(
			const Rect& rect,
			float radius_x,
			float radius_y
		);

		// 画图片
		void DrawImage(
			ImagePtr image,
			float opacity = 1.f
		);

		// 画文字
		void DrawText(
			String const& text,		/* 文字 */
			Point const& point		/* 文字位置 */
		);

		// 画几何图形边框
		void DrawGeometry(
			GeometryPtr geo
		);

		// 填充圆形
		void FillCircle(
			const Point& center,
			float radius
		);

		// 填充椭圆形
		void FillEllipse(
			const Point& center,
			float radius_x,
			float radius_y
		);

		// 填充矩形
		void FillRect(
			const Rect& rect
		);

		// 填充圆角矩形
		void FillRoundedRect(
			const Rect& rect,
			float radius_x,
			float radius_y
		);

		// 填充几何图形
		void FillGeometry(
			GeometryPtr geo
		);

		// 开始绘制路径
		void BeginPath(
			Point const& begin_pos	/* 路径起始点 */
		);

		// 结束路径
		void EndPath(
			bool closed = true		/* 路径是否闭合 */
		);

		// 添加一条线段
		void AddLine(
			Point const& point		/* 端点 */
		);

		// 添加多条线段
		void AddLines(
			Array<Point> const& points
		);

		// 添加一条三次方贝塞尔曲线
		void AddBezier(
			Point const& point1,	/* 贝塞尔曲线的第一个控制点 */
			Point const& point2,	/* 贝塞尔曲线的第二个控制点 */
			Point const& point3		/* 贝塞尔曲线的终点 */
		);

		// 添加弧线
		void AddArc(
			Point const& point,		/* 终点 */
			Point const& radius,	/* 椭圆半径 */
			float rotation,			/* 椭圆旋转角度 */
			bool clockwise = true,	/* 顺时针 or 逆时针 */
			bool is_small = true	/* 是否取小于 180° 的弧 */
		);

		// 路径描边
		void StrokePath();

		// 路径填充
		void FillPath();

		// 清空画布
		void Clear();

		// 设置填充颜色
		void SetFillColor(
			const Color& color
		);

		// 设置线条颜色
		void SetStrokeColor(
			const Color& color
		);

		// 设置线条宽度
		void SetStrokeWidth(
			float width
		);

		// 设置线条相交样式
		void SetOutlineJoinStyle(
			StrokeStyle outline_join
		);

		// 设置文字画刷样式
		void SetTextStyle(
			Font const& font,
			TextStyle const& text_style
		);

		// 获取填充颜色
		Color GetFillColor() const;

		// 获取线条颜色
		Color GetStrokeColor() const;

		// 获取线条宽度
		float GetStrokeWidth() const;

		// 变换画笔
		void SetBrushTransform(
			Matrix const& transform
		);

		// 导出为图片
		ImagePtr ExportToImage() const;

		void OnRender() override;

	protected:
		ComPtr<ID2D1Bitmap> const& GetBitmap() const;

	protected:
		float						stroke_width_;
		Font						text_font_;
		TextStyle					text_style_;

		ComPtr<ID2D1PathGeometry>		current_geometry_;
		ComPtr<ID2D1GeometrySink>		current_sink_;
		ComPtr<ID2D1StrokeStyle>		outline_join_style_;
		ComPtr<ID2D1SolidColorBrush>	fill_brush_;
		ComPtr<ID2D1SolidColorBrush>	stroke_brush_;
		ComPtr<IDWriteTextFormat>		text_format_;
		ComPtr<ITextRenderer>			text_renderer_;
		ComPtr<ID2D1BitmapRenderTarget>	render_target_;

		mutable bool					cache_expired_;
		mutable ComPtr<ID2D1Bitmap>		bitmap_cached_;
	};
}