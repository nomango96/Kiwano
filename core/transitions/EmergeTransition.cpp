#include "..\e2dtransition.h"
#include "..\e2dobject.h"

e2d::EmergeTransition::EmergeTransition(float duration)
	: Transition(duration)
{
}

void e2d::EmergeTransition::Init(Scene * prev, Scene * next)
{
	Transition::Init(prev, next);
	
	out_layer_param_.opacity = 1;
	in_layer_param_.opacity = 0;
}

void e2d::EmergeTransition::Update()
{
	Transition::Update();

	out_layer_param_.opacity = 1 - delta_;
	in_layer_param_.opacity = delta_;

	if (delta_ >= 1)
	{
		this->Stop();
	}
}
