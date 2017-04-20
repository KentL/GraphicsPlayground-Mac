#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "Node.h"
#include "Frustum.h"

namespace Geometry
{
	FrustumNode::FrustumNode(float fov, float far, float near, const string&name) :Node(name)
	{
		this->fov = fov;
		this->farPane = far;
		this->nearPane = near;
	}

	FrustumNode::~FrustumNode()
	{
		
	}
	void FrustumNode::setFOV(float fov)
	{
		this->fov = fov;
	}
	void FrustumNode::setFar(float far)
	{
		this->farPane = far;
	}
	void FrustumNode::setNear(float near)
	{
		this->nearPane = near;
	}
	void FrustumNode::setVertices(vec4* verticesArray)
	{
		for (int i = 0; i < 8; i++)
		{
			vertices[i] = verticesArray[i];
		}
	}
	float FrustumNode::getFar()
	{
		return farPane;
	}
	float FrustumNode::getNear()
	{
		return farPane;
	}
	float FrustumNode::getFOV()
	{
		return farPane;
	}
	vec4* FrustumNode::getVertices()
	{
		return vertices;
	}
	vec3* FrustumNode::getNormalFromVertices()
	{
		vec3 tempVector1, tempVector2;
		vec3 normalVector;
		vec4* vertices_data = getVertices();

		//get the near pane normal
		tempVector1 = vec3(vertices_data[1] - vertices_data[0]);
		tempVector2 = vec3(vertices_data[2] - vertices_data[0]);
		normalVector = normalize(cross(tempVector1, tempVector2));
		normals[0] = normalVector;

		//get the far pane normal
		tempVector1 = vec3(vertices_data[5] - vertices_data[4]);
		tempVector2 = vec3(vertices_data[6] - vertices_data[4]);
		normalVector = normalize(-cross(tempVector1, tempVector2));
		normals[1] = normalVector;

		//get the left pane normal
		tempVector1 = vec3(vertices_data[0] - vertices_data[4]);
		tempVector2 = vec3(vertices_data[6] - vertices_data[4]);
		normalVector = normalize(cross(tempVector1, tempVector2));
		normals[2] = normalVector;

		//get the right pane normal
		tempVector1 = vec3(vertices_data[7] - vertices_data[5]);
		tempVector2 = vec3(vertices_data[1] - vertices_data[5]);
		normalVector = normalize(cross(tempVector1, tempVector2));
		normals[3] = normalVector;

		//get the top pane normal
		tempVector1 = vec3(vertices_data[1] - vertices_data[5]);
		tempVector2 = vec3(vertices_data[4] - vertices_data[5]);
		normalVector = normalize(cross(tempVector1, tempVector2));
		normals[4] = normalVector;

		//get the bottom pane normal
		tempVector1 = vec3(vertices_data[6] - vertices_data[7]);
		tempVector2 = vec3(vertices_data[3] - vertices_data[7]);
		normalVector = normalize(cross(tempVector1, tempVector2));
		normals[5] = normalVector;

		return normals;
	}
	float* FrustumNode::getDistanceFromVertices()
	{
		vec3 tempVector;

		//get near pane distance
		tempVector =  vec3(vertices[0]);
		distance[0] = dot(tempVector, normals[0]);

		//get far pane distance
		tempVector = vec3(vertices[4]);
		distance[1] = dot(tempVector, normals[1]);

		//get left pane distance
		tempVector =  vec3(vertices[4]);
		distance[2] = dot(tempVector, normals[2]);

		//get right pane distance
		tempVector =  vec3(vertices[5]);
		distance[3] = dot(tempVector, normals[3]);

		//get top pane distance
		tempVector =  vec3(vertices[5]);
		distance[4] = dot(tempVector, normals[4]);

		//get bottom pane distance
		tempVector =  vec3(vertices[6]);
		distance[5] = dot(tempVector, normals[5]);


		return distance;
	}

}