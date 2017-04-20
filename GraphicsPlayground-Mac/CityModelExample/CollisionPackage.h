#ifndef COLLISIONPACKAGE
#define COLLISIONPACKAGE

#include "stdafx.h"	

using namespace glm;

class CollisionPackage {
public:
	vec3 eRadius; // ellipsoid radius
	// Information about the move being requested: (in R3)
	vec3 R3Velocity;
	vec3 R3Position;
	// Information about the move being requested: (in eSpace)
	vec3 velocity;
	vec3 normalizedVelocity;
	vec3 basePoint;
	// Hit information
	bool foundCollision;
	double nearestDistance;
	vec3 intersectionPoint;
};

#endif