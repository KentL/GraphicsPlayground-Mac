#include"ColorBlendingAffector.h"
#include"HelperFunction.h"

using namespace helper;

ColorBlendingAffector::ColorBlendingAffector() {}

ColorBlendingAffector::~ColorBlendingAffector(){}

void ColorBlendingAffector::apply(float delta, particle* p)
{
	if (mode == "over_life")
	{
		float blend_speed = (turnStrToNum(end) - turnStrToNum(start)) / p->lifetime;

		this->setBlendSpeed(blend_speed);
		this->setDuration(p->lifetime);

		p->color.a += blend_speed*delta;
	}
	else
	{
		if (p->age < end_time && p->age > start_time)
		{
			float blend_speed = (turnStrToNum(end) - turnStrToNum(start)) / (end_time - start_time);

			this->setBlendSpeed(blend_speed);
			this->setDuration((end_time - start_time));

			p->color.a += blend_speed*delta;
		}
	}
}

void ColorBlendingAffector::setBlendSpeed(float speed)
{
	this->blend_speed = speed;
}
