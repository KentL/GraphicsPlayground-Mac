#include "DirectionalLight.h"

void DirectionalLight::rotate(float angle)
{
	direction = vec3(vec4(direction.x, direction.y, direction.z , 1) * getRotationMatrix());
}

