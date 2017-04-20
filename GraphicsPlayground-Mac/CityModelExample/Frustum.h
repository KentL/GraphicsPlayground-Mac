#ifndef FRUSTUM
#define FRUSTUM
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "Node.h"
namespace Geometry
{
	class FrustumNode :public Node
	{
	private:
		float nearPane, farPane;
		float fov;
		vec4 vertices[8];
		vec3  normals[6];
		float distance[6];
	public:
		FrustumNode(float fov = 0, float far = 0, float near = 0, const string&name = "");
		~FrustumNode();
		void setFOV(float fov);
		void setFar(float far);
		void setNear(float near);
		void setVertices(vec4* verticesArray);
		float getFar();
		float getNear();
		float getFOV();
		vec4* getVertices();
		vec3* getNormalFromVertices();
		float* getDistanceFromVertices();
	};
}
#endif
