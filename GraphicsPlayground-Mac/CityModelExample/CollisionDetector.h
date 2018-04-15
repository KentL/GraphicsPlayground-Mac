#ifndef COLLISIONDETECTOR
#define COLLISIONDETECTOR

#include "AABBCollider.h"
#include "SphereCollider.h"
#include "Geometry/Ray.h"
using namespace Geometry;
using namespace Colliders;

class CollisionDetector
{
private:
	static vec3 g_default_intersect_point;

public:
	CollisionDetector();
	~CollisionDetector();

	///<summary>
	///Detect if the given AABB and Sphere collide with each other
	///</summary>
	static bool Does_AABB_Sphere_Collide(Colliders::AABBCollider* aabb_collider, Colliders::SphereCollider* sphere_collider);

	///<summary>
	///Detect if the given Plane and Ray intersect.The third parameter is optional.If the ray intersect with the plane, the third
	///parameter would be a vector representing the intersection point.
	///</summary>
	static bool Does_Plane_Ray_Intersect(Geometry::Plane* plane, Geometry::Ray* ray, vec3& intersection_point = g_default_intersect_point);

	///<summary>
	///Get the first intersection plane of an AABB and a ray, return null if the intersetion point doesn't exist
	///</summary>
	static Plane* GetAABBRayFirstCollidePlane(Colliders::AABBCollider* aabb_collider, Geometry::Ray* ray);
};

#endif
