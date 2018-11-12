#pragma once

#include "Node.h"
#include "struct.h"
#include "W_Material.h"
#include <Renderable.hpp>
#include <Node.h>

namespace Geometry
{
	class RenderableSphere:public Renderable, protected Node
	{
	protected:
		float radius = 1;
		float accurity = 0.1; 
	public:
		RenderableSphere();
		virtual void setRadius(float r);
		virtual void setLocation(vec3 location);
		~RenderableSphere();

	};

	
}
