#ifndef PLANE
#define PLANE

#include "stdafx.h"

using namespace glm;

namespace Geometry
{
	class Plane
	{
	public:
		double distance;
		vec3 normal;
		vec3 origin;
		float equation[4];

		Plane();
		Plane::Plane(const vec3& origin, const vec3& normal) {
			this->normal = normal;
			this->origin = origin;
			equation[0] = normal.x;
			equation[1] = normal.y;
			equation[2] = normal.z;
			equation[3] = -(normal.x*origin.x + normal.y*origin.y
				+ normal.z*origin.z);
		}

		//Construct from distance and normal
		Plane(vec3 n, double d)
		{
			distance = d; 
			normal = n;
			equation[0] = normal.x;
			equation[1] = normal.y;
			equation[2] = normal.z;
			equation[3] = -(normal.x*origin.x + normal.y*origin.y+ normal.z*origin.z);
		}
		// Construct from triangle:
		Plane(const vec3& p1, const vec3& p2,const vec3& p3)
		{
			normal = glm::cross((p2 - p1),(p3 - p1));
			normal=glm::normalize(normal);
			origin = p1;
			equation[0] = normal.x;
			equation[1] = normal.y;
			equation[2] = normal.z;
			equation[3] = -(normal.x*origin.x + normal.y*origin.y+ normal.z*origin.z);
		}

		Plane(const vec3& p1, const vec3& p2, const vec3& p3, const vec3& n)
		{
			normal = glm::normalize(n);
			origin = p1;
			equation[0] = normal.x;
			equation[1] = normal.y;
			equation[2] = normal.z;
			equation[3] = -(normal.x*origin.x + normal.y*origin.y + normal.z*origin.z);
		}
		~Plane(){};

		///<summary>
		///This function set the distance used to determine the position of the plane
		///</summary>
		void SetDistance(double d){ distance = d; }


		///<summary>
		///This function set the normal used to determine the direction of the plane
		///</summary>
		void SetNormal(vec3 n){ normal = n; }


		///<summary>
		///This function return the distance used to determine the position of the plane
		///</summary>
		double GetDistance() const { return distance; }

		///<summary>
		///This function return the normal used to determine the direction of the plane
		///</summary>
		vec3 GetNormal() const { return normal; }

		///<summary>
		///This function detect if the direction is face toward the front face of the plane
		///</summary>
		bool IsFrontFacingTo(const vec3& direction) const
		{
			double dot = glm::dot(normal,direction);
			return (dot <= 0);
		}

		///<summary>
		///This function gets the signed distance to a point
		///</summary>
		double signedDistanceTo(const vec3& point) const
		{
			return (glm::dot(point,normal)) + equation[3];
		}

	};

}


#endif