#include "ColorAffector.h"
#include "HelperFunction.h"

using namespace helper;
ColorAffector::ColorAffector() {}

ColorAffector::~ColorAffector(){}

void ColorAffector::apply(float delta, particle* p)
{
	if (mode == "over_life")
	{
		vec3 color_speed = (turnStrToVector_3D(end) - turnStrToVector_3D(start)) / p->lifetime;

		this->setColorChangeSpeed(color_speed);
		this->setDuration(p->lifetime);

		p->color.r += r_speed*delta;
		p->color.g += g_speed*delta;
		p->color.b += b_speed*delta;
	}
	else
	{
		if (p->age < end_time && p->age > start_time)
		{
			vec3 color_speed = (turnStrToVector_3D(end) - turnStrToVector_3D(start)) / (end_time - start_time);

			this->setColorChangeSpeed(color_speed);
			this->setDuration(end_time - start_time);

			p->color.r += r_speed*delta;
			p->color.g += g_speed*delta;
			p->color.b += b_speed*delta;
		}
	}
}

void ColorAffector::setColorChangeSpeed(vec3 speed)
{
	this->r_speed = speed.r;
	this->g_speed = speed.g;
	this->b_speed = speed.b;
}
