#ifndef COLLIDER
#define COLLIDER

#include "stdafx.h"

using namespace glm;
namespace Colliders
{
	enum ColliderType
	{
		Sphere,
		AABB
	};

	class Collider
	{
	protected:
		ColliderType collider_type;
		vec3 position;
	public:
		Collider();
		~Collider();
		void SetPosition(vec3 pos){ position = pos; }
		vec3 GetPosition() const{ return position; }
	};
}


#endif