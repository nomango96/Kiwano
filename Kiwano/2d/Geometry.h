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
#include "include-forwards.h"
#include <d2d1.h>

namespace kiwano
{
	// 几何抽象
	class KGE_API Geometry
		: public virtual Object
	{
		friend class Canvas;
		friend class GeometryNode;

	public:
		Geometry();

		virtual ~Geometry();

		// 获取外切包围盒
		Rect GetBoundingBox();

		// 判断图形是否包含点
		bool ContainsPoint(
			Point const& point
		);

		// 获取图形展开成一条直线的长度
		float GetLength();

		// 计算图形路径上点的位置和切线向量
		bool ComputePointAt(
			float length,
			Point* point,
			Point* tangent
		);

		// 计算面积
		float ComputeArea();

	protected:
		ComPtr<ID2D1Geometry> geo_;
	};


	// 直线
	class KGE_API LineGeometry
		: public Geometry
	{
	public:
		LineGeometry();

		LineGeometry(
			Point const& begin,
			Point const& end
		);

		virtual ~LineGeometry();

		Point const& GetBegin() const { return begin_; }

		Point const& GetEnd() const { return end_; }

		void SetLine(
			Point const& begin,
			Point const& end
		);

		void SetBegin(
			Point const& begin
		);

		void SetEnd(
			Point const& end
		);

	protected:
		Point begin_;
		Point end_;
	};


	// 几何矩形
	class KGE_API RectangleGeometry
		: public Geometry
	{
	public:
		RectangleGeometry();

		RectangleGeometry(
			Rect const& rect
		);

		RectangleGeometry(
			Point const& left_top,
			Size const& size
		);

		virtual ~RectangleGeometry();

		Rect const& GetRect() const { return rect_; }

		void SetRect(Rect const& rect);

	protected:
		Rect rect_;
	};


	// 几何圆形
	class KGE_API CircleGeometry
		: public Geometry
	{
	public:
		CircleGeometry();

		CircleGeometry(
			Point const& center,
			float radius
		);

		virtual ~CircleGeometry();

		float GetRadius() const { return radius_; }

		void SetRadius(
			float radius
		);

		Point const& GetCenter() const { return center_; }

		void SetCenter(
			Point const& center
		);

		void SetCircle(
			Point const& center,
			float radius
		);

	protected:
		Point center_;
		float radius_;
	};


	// 几何椭圆
	class KGE_API EllipseGeometry
		: public Geometry
	{
	public:
		EllipseGeometry();

		EllipseGeometry(
			Point const& center,
			float radius_x,
			float radius_y
		);

		virtual ~EllipseGeometry();

		float GetRadiusX() const { return radius_x_; }

		float GetRadiusY() const { return radius_y_; }

		void SetRadius(
			float radius_x,
			float radius_y
		);

		Point const& GetCenter() const { return center_; }

		void SetCenter(
			Point const& center
		);

		void SetEllipse(
			Point const& center,
			float radius_x,
			float radius_y
		);

	protected:
		Point center_;
		float radius_x_;
		float radius_y_;
	};


	// 几何路径
	class KGE_API PathGeometry
		: public Geometry
	{
	public:
		PathGeometry();

		virtual ~PathGeometry();

		// 开始添加路径
		void BeginPath(
			Point const& begin_pos = Point{}	/* 起始点 */
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
			Size const& radius,		/* 椭圆半径 */
			float rotation,			/* 椭圆旋转角度 */
			bool clockwise = true,	/* 顺时针 or 逆时针 */
			bool is_small = true	/* 是否取小于 180° 的弧 */
		);

		// 清除路径
		void ClearPath();

	protected:
		ComPtr<ID2D1PathGeometry>	current_geometry_;
		ComPtr<ID2D1GeometrySink>	current_sink_;
	};


	// 几何圆角矩形
	class KGE_API RoundedRectGeometry
		: public Geometry
	{
	public:
		RoundedRectGeometry();

		RoundedRectGeometry(
			Rect const& rect,
			float radius_x,
			float radius_y
		);

		virtual ~RoundedRectGeometry();

		float GetRadiusX() const { return radius_x_; }

		float GetRadiusY() const { return radius_y_; }

		void SetRadius(
			float radius_x,
			float radius_y
		);

		Rect const& GetRect() const { return rect_; }

		void SetRect(
			Rect const& rect
		);

		void SetRoundedRect(
			Rect const& rect,
			float radius_x,
			float radius_y
		);

	protected:
		Rect	rect_;
		float	radius_x_;
		float	radius_y_;
	};
}
