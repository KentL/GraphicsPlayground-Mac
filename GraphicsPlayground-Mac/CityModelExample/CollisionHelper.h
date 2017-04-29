#ifndef COLLISIONHELPER
#define COLLISIONHELPER
#include "stdafx.h"
#include "CollisionPackage.h"
#include "Plane.h"
#include "Triangle.h"
#include "struct.h"
#include "Helper.h"

using namespace glm;
using namespace Geometry;


typedef unsigned int uint32;
#define in(a) ((uint32&) a)

bool checkPointInTriangle(const vec3& point, const vec3& pa, const vec3& pb, const vec3& pc)
{
	vec3 e10 = pb - pa;
	vec3 e20 = pc - pa;
	float a = dot(e10, e10);
	float b = dot(e10, e20);
	float c = dot(e20, e20);
	float ac_bb = (a*c) - (b*b);
	vec3 vp(point.x - pa.x, point.y - pa.y, point.z - pa.z);
	float d = dot(vp, e10);
	float e = dot(vp, e20);
	float x = (d*c) - (e*b);
	float y = (e*a) - (d*b);
	float z = x + y - ac_bb;
	return ((in(z)& ~(in(x) | in(y))) & 0x80000000);
}

// Assumes: p1,p2 and p3 are given in ellisoid space:
void CheckTriangle(CollisionPackage* colPackage, const vec3& p1, const vec3& p2, const vec3& p3,vec3 normal)
{
	// Make the plane containing this triangle.
	Plane trianglePlane = Plane(p1, p2, p3,normal);
	// Is triangle front-facing to the velocity vec3?
	// We only check front-facing triangles
	// (your choice of course)
	if (trianglePlane.IsFrontFacingTo(colPackage->normalizedVelocity))
	{
		// Get interval of plane intersection:
		double t0, t1;
		bool embeddedInPlane = false;
		// Calculate the signed distance from sphere
		// position to triangle plane
		double signedDistToTrianglePlane = trianglePlane.signedDistanceTo(colPackage->basePoint);
		// cache this as we¡¯re going to use it a few times below:
		float normalDotVelocity = glm::dot(trianglePlane.normal, colPackage->velocity);
		// if sphere is travelling parrallel to the plane:
		if (normalDotVelocity == 0.0f) 
		{
			if (fabs(signedDistToTrianglePlane) >= 1.0f)
			{
				// Sphere is not embedded in plane.
				// No collision possible:
				return;
			}
			else {
				// sphere is embedded in plane.
				// It intersects in the whole range [0..1]
				embeddedInPlane = true;
				t0 = 0.0;
				t1 = 1.0;
			}
		}
		else {
			// N dot D is not 0. Calculate intersection interval:
			t0 = (-1.0 - signedDistToTrianglePlane) / normalDotVelocity;
			t1 = (1.0 - signedDistToTrianglePlane) / normalDotVelocity;
			// Swap so t0 < t1
			if (t0 > t1) 
			{
				double temp = t1;
				t1 = t0;
				t0 = temp;
			}
			// Check that at least one result is within range:
			if (t0 > 1.0f || t1 < 0.0f) 
			{
				// Both t values are outside values [0,1]
				// No collision possible:
				return;
			}
			// Clamp to [0,1]
			if (t0 < 0.0) t0 = 0.0;
			if (t1 < 0.0) t1 = 0.0;
			if (t0 > 1.0) t0 = 1.0;
			if (t1 > 1.0) t1 = 1.0;
		}
		// OK, at this point we have two time values t0 and t1
		// between which the swept sphere intersects with the
		// triangle plane. If any collision is to occur it must
		// happen within this interval.
		vec3 collisionPoint;
		bool foundCollison = false;
		float t = 1.0;
		// First we check for the easy case - collision inside
		// the triangle. If this happens it must be at time t0
		// as this is when the sphere rests on the front side
		// of the triangle plane. Note, this can only happen if
		// the sphere is not embedded in the triangle plane.
		if (!embeddedInPlane) 
		{
			vec3 planeIntersectionPoint = (colPackage->basePoint - trianglePlane.normal) + colPackage->velocity*vec3(t0, t0, t0);
			if (checkPointInTriangle(planeIntersectionPoint, p1, p2, p3))
			{
				foundCollison = true;
				t = t0;
				collisionPoint = planeIntersectionPoint;
			}
		}
		// if we haven¡¯t found a collision already we¡¯ll have to
		// sweep sphere against points and edges of the triangle.
		// Note: A collision inside the triangle (the check above)
		// will always happen before a vertex or edge collision!
		// This is why we can skip the swept test if the above
		// gives a collision!
		if (foundCollison == false) 
		{
			// some commonly used terms:
			vec3 velocity = colPackage->velocity;
			vec3 base = colPackage->basePoint;
			float velocitySquaredLength = SquaredLength(velocity);
			float a, b, c; // Params for equation
			float newT;
			// For each vertex or edge a quadratic equation have to
			// be solved. We parameterize this equation as
			// a*t^2 + b*t + c = 0 and below we calculate the
			// parameters a,b and c for each test.
			// Check against points:
			a = velocitySquaredLength;
			// P1
			b = 2.0*(glm::dot(velocity, (base - p1)));
			c = SquaredLength((p1 - base)) - 1.0;
			if (getLowestRoot(a, b, c, t, &newT)) 
			{
				t = newT;
				foundCollison = true;
				collisionPoint = p1;
			}
			// P2
			b = 2.0*(dot(velocity, (base - p2)));
			c = SquaredLength((p2 - base)) - 1.0;
			if (getLowestRoot(a, b, c, t, &newT))
			{
				t = newT;
				foundCollison = true;
				collisionPoint = p2;
			}
			// P3
			vec3 temp1 = (base - p3);
			vec3 temp2 = (p3 - base);
			b = 2.0*(dot(velocity, temp1));
			c = SquaredLength(temp2) - 1.0;
			if (getLowestRoot(a, b, c, t, &newT))
			{
				t = newT;
				foundCollison = true;
				collisionPoint = p3;
			}
			// Check agains edges:
			// p1 -> p2:
			vec3 edge = p2 - p1;
			vec3 baseToVertex = p1 - base;
			float edgeSquaredLength = SquaredLength(edge);
			float edgeDotVelocity = dot(edge, velocity);
			float edgeDotBaseToVertex = dot(edge, baseToVertex);
			// Calculate parameters for equation
			a = edgeSquaredLength*-velocitySquaredLength + edgeDotVelocity*edgeDotVelocity;
			b = edgeSquaredLength*(2 * dot(velocity, baseToVertex)) - 2.0*edgeDotVelocity*edgeDotBaseToVertex;
			c = edgeSquaredLength*(1 - SquaredLength(baseToVertex)) + edgeDotBaseToVertex*edgeDotBaseToVertex;
			// Does the swept sphere collide against infinite edge?
			if (getLowestRoot(a, b, c, t, &newT)) 
			{
				// Check if intersection is within line segment:
				float f = (edgeDotVelocity*newT - edgeDotBaseToVertex) / edgeSquaredLength;
				if (f >= 0.0 && f <= 1.0) 
				{
					// intersection took place within segment.
					t = newT;
					foundCollison = true;
					collisionPoint = p1 + f*edge;
				}
			}
			// p2 -> p3:
			edge = p3 - p2;
			baseToVertex = p2 - base;
			edgeSquaredLength = SquaredLength(edge);
			edgeDotVelocity = dot(edge, velocity);
			edgeDotBaseToVertex = dot(edge, baseToVertex);
			a = edgeSquaredLength*-velocitySquaredLength + edgeDotVelocity*edgeDotVelocity;
			b = edgeSquaredLength*(2 * dot(velocity, baseToVertex)) - 2.0*edgeDotVelocity*edgeDotBaseToVertex;
			c = edgeSquaredLength*(1 - SquaredLength(baseToVertex)) + edgeDotBaseToVertex*edgeDotBaseToVertex;
			if (getLowestRoot(a, b, c, t, &newT)) 
			{
				float f = (edgeDotVelocity*newT - edgeDotBaseToVertex) /edgeSquaredLength;
				if (f >= 0.0 && f <= 1.0) 
				{
					t = newT;
					foundCollison = true;
					collisionPoint = p2 + f*edge;
				}
			}
			// p3 -> p1:
			edge = p1 - p3;
			baseToVertex = p3 - base;
			edgeSquaredLength = SquaredLength(edge);
			edgeDotVelocity = dot(edge, velocity);
			edgeDotBaseToVertex = dot(edge, baseToVertex);
			a = edgeSquaredLength*-velocitySquaredLength + edgeDotVelocity*edgeDotVelocity;
			b = edgeSquaredLength*(2 * dot(velocity, baseToVertex)) - 2.0*edgeDotVelocity*edgeDotBaseToVertex;
			c = edgeSquaredLength*(1 - SquaredLength(baseToVertex)) + edgeDotBaseToVertex*edgeDotBaseToVertex;
			if (getLowestRoot(a, b, c, t, &newT)) 
			{
				float f = (edgeDotVelocity*newT - edgeDotBaseToVertex) /edgeSquaredLength;
				if (f >= 0.0 && f <= 1.0) 
				{
					t = newT;
					foundCollison = true;
					collisionPoint = p3 + f*edge;
				}
			}
		}
		// Set result:
		if (foundCollison == true) 
		{
			// distance to collision: ¡¯t¡¯ is time of collision
			double distToCollision = t*GetLength(colPackage->velocity);
			// Does this triangle qualify for the closest hit?
			// it does if it¡¯s the first hit or the closest
			if (colPackage->foundCollision == false ||distToCollision < colPackage->nearestDistance) 
			{
				// Collision information nessesary for sliding
				colPackage->nearestDistance = distToCollision;
				colPackage->intersectionPoint = collisionPoint;
				colPackage->foundCollision = true;
			}
		}
	} // if not backface
}

void ConstructTriangleFromAABB(AABBCollider* aabb,Geometry::Triangle* triangle_array)
{
	double width = aabb->GetWidth();
	double height = aabb->GetHeight();
	double length = aabb->GetLength();
	vec3 pos = aabb->GetPosition();

	vec3 vertices[8];
	vertices[0] = pos + vec3(-length/2,height/2,-width/2);
	vertices[1] = pos + vec3(length/ 2, height / 2, -width / 2);
	vertices[2] = pos + vec3(length/ 2, -height / 2, -width / 2);
	vertices[3] = pos + vec3(-length/ 2, -height / 2, -width / 2);

	vertices[4] = pos + vec3(-length / 2, height / 2, width / 2);
	vertices[5] = pos + vec3(length / 2, height / 2, width / 2);
	vertices[6] = pos + vec3(length / 2, -height / 2, width / 2);
	vertices[7] = pos + vec3(-length / 2, -height / 2, width / 2);

	vec3 front_normal = vec3(0, 0, -1);
	vec3 back_normal = vec3(0, 0, 1);
	vec3 left_normal = vec3(-1, 0, 0);
	vec3 right_normal = vec3(1, 0, 0);
	vec3 top_normal = vec3(0, 1, 0);
	vec3 bottom_normal = vec3(0, -1, 0);

	triangle_array[0] = Triangle(vertices[0], vertices[3], vertices[2], front_normal);
	triangle_array[1] = Triangle(vertices[0], vertices[1], vertices[2],front_normal);
	triangle_array[2] = Triangle(vertices[6], vertices[1], vertices[2], right_normal);
	triangle_array[3] = Triangle(vertices[1], vertices[5], vertices[6], right_normal);
	triangle_array[4] = Triangle(vertices[4], vertices[6], vertices[7],back_normal);
	triangle_array[5] = Triangle(vertices[4], vertices[5], vertices[6],back_normal);
	triangle_array[6] = Triangle(vertices[0], vertices[3], vertices[7],left_normal);
	triangle_array[7] = Triangle(vertices[0], vertices[4], vertices[7],left_normal);
	triangle_array[8] = Triangle(vertices[0], vertices[4], vertices[5],top_normal);
	triangle_array[9] = Triangle(vertices[0], vertices[1], vertices[5],top_normal);
	triangle_array[10] = Triangle(vertices[3], vertices[2], vertices[6],bottom_normal);
	triangle_array[11] = Triangle(vertices[3], vertices[6], vertices[7],bottom_normal);
}

void LoadColliderVertexBuffer(vector<AABBCollider*>* aabbs, Vertex1* a, int &count)
{
	for (int i = 0; i < aabbs->size(); i++)
	{
		double width = aabbs->at(i)->GetWidth();
		double height = aabbs->at(i)->GetHeight();
		double length = aabbs->at(i)->GetLength();
		vec3 pos = aabbs->at(i)->GetPosition();

		vec3 vertices[8];
		vertices[0] = pos + vec3(-width / 2, height / 2, length / 2);
		vertices[1] = pos + vec3(width / 2, height / 2, length / 2);
		vertices[2] = pos + vec3(width / 2, -height / 2, length / 2);
		vertices[3] = pos + vec3(-width / 2, -height / 2, length / 2);

		vertices[4] = pos + vec3(-width / 2, height / 2, -length / 2);
		vertices[5] = pos + vec3(width / 2, height / 2, -length / 2);
		vertices[6] = pos + vec3(width / 2, -height / 2, -length / 2);
		vertices[7] = pos + vec3(-width / 2, -height / 2, -length / 2);

		vec3 front_normal = vec3(0, 0, -1);
		vec3 back_normal = vec3(0, 0, 1);
		vec3 left_normal = vec3(-1, 0, 0);
		vec3 right_normal = vec3(1, 0, 0);
		vec3 top_normal = vec3(0, 1, 0);
		vec3 bottom_normal = vec3(0, -1, 0);

		a[i * 8 + 0] = { vertices[0].x, vertices[0].y, vertices[0].z};
		a[i * 8 + 1] = { vertices[1].x, vertices[1].y, vertices[1].z };
		a[i * 8 + 2] = { vertices[1].x, vertices[1].y, vertices[1].z };
		a[i * 8 + 2] = { vertices[5].x, vertices[5].y, vertices[5].z };
		a[i * 8 + 2] = { vertices[5].x, vertices[5].y, vertices[5].z };
		a[i * 8 + 2] = { vertices[4].x, vertices[4].y, vertices[4].z };
		a[i * 8 + 2] = { vertices[4].x, vertices[4].y, vertices[4].z };
		a[i * 8 + 2] = { vertices[0].x, vertices[0].y, vertices[0].z };
		
		count += 8;
	}
}

#endif
