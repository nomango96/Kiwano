// Copyright (c) 2016-2018 Easy2D - Nomango
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

#include "..\e2dmodule.h"
#include "..\e2dobject.h"

e2d::Scene::Scene()
	: root_(nullptr)
	, transform_(D2D1::Matrix3x2F::Identity())
{
}

e2d::Scene::Scene(Node * root)
	: root_(nullptr)
	, transform_(D2D1::Matrix3x2F::Identity())
{
	this->SetRoot(root);
}

e2d::Scene::~Scene()
{
	if (root_)
	{
		root_->SetParentScene(nullptr);
		root_->Release();
	}
}

void e2d::Scene::SetRoot(Node * root)
{
	if (root_ == root)
		return;

	if (root_)
	{
		root_->SetParentScene(nullptr);
		root_->Release();
	}

	if (root)
	{
		root->Retain();
		root->SetParentScene(this);
	}

	root_ = root;
}

e2d::Node * e2d::Scene::GetRoot() const
{
	return root_;
}

void e2d::Scene::Draw()
{
	if (root_)
	{
		root_->Visit();
	}
}

void e2d::Scene::Dispatch(const MouseEvent & e)
{
	if (root_)
	{
		root_->Dispatch(e, false);
	}
}

void e2d::Scene::Dispatch(const KeyEvent & e)
{
	if (root_)
	{
		root_->Dispatch(e, false);
	}
}

void e2d::Scene::SetTransform(const D2D1::Matrix3x2F& matrix)
{
	transform_ = matrix;

	if (root_)
	{
		root_->dirty_transform_ = true;
	}
}

const D2D1::Matrix3x2F & e2d::Scene::GetTransform() const
{
	return transform_;
}