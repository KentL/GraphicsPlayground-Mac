#include"ScaleAffector.h"
#include"HelperFunction.h"

#define SCALE_MULTI_FACTOR 0.1

using namespace helper;

ScaleAffector::ScaleAffector() {}

ScaleAffector::~ScaleAffector(){}

void ScaleAffector::apply(float delta, particle* p)
{
	if (mode == "over_life")
	{
		float scale_speed = (turnStrToNum(end) - turnStrToNum(start))*p->size / p->lifetime ;
		this->setDuration(p->lifetime);
		this->setScaleSpeed(scale_speed);
		p->size += scale_speed*delta*SCALE_MULTI_FACTOR;
	}
	else
	{
		if (p->age < end_time && p->age > start_time)
		{
			float scale_speed = (turnStrToNum(end) - turnStrToNum(start))*p->size / p->lifetime;
			this->setDuration(end_time-start_time);
			this->setScaleSpeed(scale_speed);

			p->size += scale_speed*delta*SCALE_MULTI_FACTOR;
		}
	}
}

void ScaleAffector::setScaleSpeed(float speed)
{
	this->scale_speed = speed;
}
