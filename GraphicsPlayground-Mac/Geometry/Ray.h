#ifndef RAY;
#define RAY

#include "stdafx.h"

using namespace glm;

namespace Geometry
{
	class Ray
	{
	private:
		vec3 origin;
		vec3 direction;
	public:
		Ray();
		Ray(vec3 ori, vec3 dir){ origin = ori; direction = dir; }
		~Ray();


		///<summary>
		///This function set the point used to determine the position of the ray
		///</summary>
		void SetOrigin(vec3 ori){ origin = ori; }


		///<summary>
		///This function set the vector used to determine the direciton of the ray
		///</summary>
		void SetDirection(vec3 dir){ direction = dir; }


		///<summary>
		///This function return the point used to determine the position of the ray
		///</summary>
		vec3 GetOrigin() const{ return origin; }


		///<summary>
		///This function return the vector used to determine the direction of the ray
		///</summary>
		vec3 GetDirection() const { return direction; }
	};

}
#endif

