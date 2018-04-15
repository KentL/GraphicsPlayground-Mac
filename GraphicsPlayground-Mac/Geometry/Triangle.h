#ifndef TRIANGLE
#define TRIANGLE

#include "stdafx.h"

using namespace glm;

namespace Geometry
{
	class Triangle
	{
	public:
		vec3 vertex1;
		vec3 vectex2;
		vec3 vectex3;
		vec3 normal;

		Triangle(vec3 v1, vec3 v2, vec3 v3,vec3 n)
		{
			vertex1 = v1;
			vectex2 = v2;
			vectex3 = v3;
			normal = n;
		}

		Triangle(){};
	};
}

#endif
