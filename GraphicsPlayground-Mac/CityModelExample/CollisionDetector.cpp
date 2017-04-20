#include "stdafx.h"
#include "CollisionDetector.h"

vec3 CollisionDetector::g_default_intersect_point = vec3(0, 0, 0);

CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::Does_AABB_Sphere_Collide(Colliders::AABBCollider* aabb_collider, Colliders::SphereCollider* sphere_collider)
{
	//min and max coordinates
	double xmin, ymin, zmin;
	double xmax, ymax, zmax;
	double length, height, width;
	double radius;
	vec3 position;
	vec3 center;

	center= sphere_collider->GetPosition();
	radius = 10*sphere_collider->getRadius();
	position = aabb_collider->GetPosition();
	length = aabb_collider->GetLength();
	height = aabb_collider->GetHeight();
	width = aabb_collider->GetWidth();

	double dist = 0;
	double delta = 0;
	xmin = position.x - length / 2;
	ymin = position.y - height / 2;
	zmin = position.z - width / 2;
	xmax = position.x + length / 2;
	ymax = position.y + height / 2;
	zmax = position.z + width / 2;

	double min_coor[] = { xmin, ymin, zmin };
	double max_coor[] = { xmax, ymax, zmax };
	double center_coor[] = { center.x, center.y, center.z };
	for (int i = 0; i < 3; i++)
	{
		delta = center_coor[i] - min_coor[i];
		if (delta<0)
		{
			if (delta<-radius)
			{
				return false;
			}
			dist += delta*delta;
		}
		else
		{
			delta = center_coor[i] - max_coor[i] ;
			if (delta>0)
			{
				if (delta>radius)
				{
					return false;
				}
				dist += delta*delta;
			}
		}
	}
	if (dist>radius*radius)
	{
		return false;
	}
	return true;
}

bool CollisionDetector::Does_Plane_Ray_Intersect(Geometry::Plane* plane, Geometry::Ray* ray, vec3& intersection_point)
{
	vec3 plane_normal,ray_origin,ray_direction;
	double plane_distance;

	plane_normal = plane->GetNormal();
	plane_distance = plane->GetDistance();
	ray_origin = ray->GetOrigin();
	ray_direction = ray->GetDirection();

	float denom = dot(plane_normal, ray_direction);
	if (abs(denom)>0)
	{
		float t = -(dot(ray_origin, plane_normal) + plane_distance) / denom;
		if (t > 0)
		{
			vec3 temp = ray_origin + t*ray_direction;
			intersection_point.x = temp.x;
			intersection_point.y = temp.y;
			intersection_point.z = temp.z;
			return true;
		}
	}
	return false;
}

Plane* CollisionDetector::GetAABBRayFirstCollidePlane(Colliders::AABBCollider* aabb_collider, Geometry::Ray* ray)
{
	Plane* planes[6];
	planes[0] = aabb_collider->GetFrontPlane();
	planes[1] = aabb_collider->GetBackPlane();
	planes[2] = aabb_collider->GetLeftPlane();
	planes[3] = aabb_collider->GetRightPlane();
	planes[4] = aabb_collider->GetTopPlane();
	planes[5] = aabb_collider->GetBottomPlane();

	vector<Plane*> intersect_planes;
	vector<vec3> intersect_points;
	int intersect_count = 0;
	int closest_index=0;
	double min_distance;

	for (int i = 0; i < 6; i++)
	{
		vec3 temp_point;
		if (Does_Plane_Ray_Intersect(planes[i],ray,temp_point)==true)
		{
			intersect_planes.push_back(planes[i]);
			intersect_points.push_back(temp_point);
			intersect_count++;
		}
	}
	if (intersect_count>0)
	{
		vec3 intersect_point = intersect_points[0];
		min_distance = glm::distance(intersect_point, ray->GetOrigin());
		closest_index = 0;

		for (int j = 1; j < intersect_count; j++)
		{
			intersect_point = intersect_points[j];
			if (min_distance>glm::distance(intersect_point, ray->GetOrigin()))
			{
				min_distance = glm::distance(intersect_point, ray->GetOrigin());
				closest_index = j;
			}
		}
		
		return intersect_planes[closest_index];
	}
	else
	{
		return NULL;
	}
}
