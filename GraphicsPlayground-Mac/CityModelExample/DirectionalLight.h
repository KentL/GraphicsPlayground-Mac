#ifndef DIRECTIONALLIGHT
#define DIRECTIONALLIGHT

#include "Light.h"

class DirectionalLight : public Light
{
private:
	vec3 direction;
public:
	DirectionalLight() :direction(0, 0, 1){};
	void setDirection(vec3 dir){ direction = dir; }
	vec3 getDirection(){ return direction; }
	void rotate(float angle);
};

#endif
