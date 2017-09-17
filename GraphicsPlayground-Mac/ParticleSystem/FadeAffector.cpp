#include"FadeAffector.h"
#include"HelperFunction.h"

using namespace helper;

FadeAffector::FadeAffector() {}

FadeAffector::~FadeAffector(){}

void FadeAffector::apply(float delta, particle* p)
{
	if (mode == "over_life")
	{
		float fade_speed = (turnStrToNum(this->start) - turnStrToNum(this->end)) / p->lifetime;
		this->setDuration(p->lifetime);
		this->setFadeSpeed(fade_speed);
		p->color.a -= fade_speed*delta;
	}
	else
	{
		if (p->age < end_time && p->age > start_time)
		{
			vec3 acc_speed = (turnStrToVector_3D(this->start) - turnStrToVector_3D(this->start)) / (end_time - start_time);
			this->setDuration(end_time - start_time);
			p->color.a -= fade_speed*delta;
		}
	}
}

void FadeAffector::setFadeSpeed(int speed)
{
	this->fade_speed = speed;
}
