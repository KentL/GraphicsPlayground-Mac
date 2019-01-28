
#include <RenderableSphere.h>

namespace Geometry
{
	RenderableSphere::RenderableSphere()
	{

	}


	RenderableSphere::~RenderableSphere()
	{

	}

	void RenderableSphere::setRadius(float r) { radius = r; this->setScale(vec3(r, r, r)); }
	
	void RenderableSphere::setLocation(vec3 location) { this->setPos(location); }

}