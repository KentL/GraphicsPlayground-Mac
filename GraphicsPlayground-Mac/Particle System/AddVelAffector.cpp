#include"AddVelAffector.h"
#include"HelperFunction.h"

using namespace helper;

AddVelAffector::AddVelAffector() {}

AddVelAffector::~AddVelAffector(){}

void AddVelAffector::setSpeedDifference(vec3 difference)
{
	this->speed_difference = difference;
}

void AddVelAffector::apply(float delta, particle* p)
{
	if (mode == "over_life")
	{
		vec3 acc_speed = speed_difference*p->velocity / p->lifetime;
		this->setDuration(p->lifetime);
		this->setAccSpeed(acc_speed);
		p->velocity += accelerate_speed*delta;
	}
	else
	{
		if (p->age < end_time && p->age > start_time)
		{
			vec3 acc_speed = (turnStrToVector_3D(this->end) - turnStrToVector_3D(this->start))*p->velocity / (end_time - start_time);
			this->setDuration(end_time-start_time);
			p->velocity += accelerate_speed*delta ;
		}
	}
}

void AddVelAffector::setAccSpeed(vec3 speed)
{
	this->accelerate_speed = speed;
}
