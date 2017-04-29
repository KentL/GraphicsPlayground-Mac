#ifndef HELPER
#define HELPER
#include "stdafx.h"
#include "CollisionPackage.h"
#include "Plane.h"
#include "Triangle.h"
#include "struct.h"

bool getLowestRoot(float a, float b, float c, float maxR, float* root) {
	// Check if a solution exists
	float determinant = b*b - 4.0f*a*c;
	// If determinant is negative it means no solutions.
	if (determinant < 0.0f) return false;
	// calculate the two roots: (if determinant == 0 then
	// x1==x2 but let¡¯s disregard that slight optimization)
	float sqrtD = sqrt(determinant);
	float r1 = (-b - sqrtD) / (2 * a);
	float r2 = (-b + sqrtD) / (2 * a);
	// Sort so x1 <= x2
	if (r1 > r2) {
		float temp = r2;
		r2 = r1;
		r1 = temp;
	}
	// Get lowest root:
	if (r1 > 0 && r1 < maxR) {
		*root = r1;
		return true;
	}
	// It is possible that we want x2 - this can happen
	// if x1 < 0
	if (r2 > 0 && r2 < maxR) {
		*root = r2;
		return true;
	}
	// No (valid) solutions
	return false;
}

double GetLength(vec3& v){ return glm::sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }

double SquaredLength(vec3 vec)
{
	return (vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

void SetLength(vec3& v, double length)
{
	v = glm::normalize(v);
	v = v*vec3(length, length, length);
}

#endif
