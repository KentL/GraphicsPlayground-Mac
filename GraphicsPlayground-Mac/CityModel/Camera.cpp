#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "W_Common.h"
#include "Camera.h"
#include <Windows.h>

#define SPEED 10

Camera::Camera() 
{
	frustum = new FrustumNode();
	addChild(frustum);
	turnLeftScale = turnUpScale = 0;
	leftDistance = forwDistance = 0;
}

Camera::~Camera()
{
	//delete frustum;
}

void Camera::setPos(vec3 pos)
{
	this->myPosition = pos;
	frustum->setPos(pos);
	dirty = true;
}

void Camera::setFOV(float fov)
{
	this->fov = fov;
	frustum->setFOV(fov);
	frustumCalculated = false;
}

void Camera::setFar(float farPane)
{
	this->farPane = farPane;
	frustum->setFar(farPane);
	frustumCalculated = false;
}

void Camera::setNear(float nearPane)
{
	this->nearPane = nearPane;
	frustum->setNear(nearPane);
	frustumCalculated = false;
}

void Camera::setAspect(float aspect)
{
	this->aspect = aspect;
}

float Camera::getNear()
{
	return this->nearPane;
}

float Camera::getFar()
{
	return this->nearPane;
}

float Camera::getFOV()
{
	return this->fov;
}

mat4 Camera::getViewMatrix()
{
	lookatPoint = this->getRotationMatrix()*vec4(0, 0, 1, 1);

	viewMatrix = glm::lookAt(this->getPos(), this->getPos() + vec3(lookatPoint), glm::vec3(0.0f, 1.0f, 0.0f));
	
	return viewMatrix;
}

vec4 Camera::getViewDirection()
{
	return lookatPoint;
}

mat4 Camera::getProjectionMatrix()
{
	projectionMatrix=glm::perspective(fov, aspect, nearPane, farPane);
	return projectionMatrix;
}

FrustumNode Camera::getFrustum()
{
	vec4 vertices_translated[8];
	vec4* vertices_data = frustum->getVertices();
	
	for (int i = 0; i < 8; i++)
	{
		vertices_translated[i] = this->getWorldTransform()*vertices_data[i];
	}
	FrustumNode tempFrustum = *frustum;
	tempFrustum.setVertices(vertices_translated);
	return tempFrustum;
}

void Camera::cameraMove()
{
	
	ShowCursor(false);
	POINT cursor;

	GetCursorPos(&cursor);

	newx = cursor.x;
	newy = cursor.y;

	if (newx > 1200 || newx < 10 || newy < 10 || newy>700)
	{
		SetCursorPos(600, 350);
		newx = lastx = 600;
		newy = lasty = 350;
	}
	if (isfirsttime)
	{
		lastx = newx;
		lasty = newy;
		isfirsttime = false;
	}
	else
	{
		turnLeftScale = turnLeftScale - (newx - lastx) / 10;
		turnUpScale = turnUpScale - (newy - lasty) / 10;
		

		if (90 - turnUpScale < 0.01)
		{
			turnUpScale = 90 - 0.01;
		}
		if (turnUpScale + 90 < 0.01)
		{
			turnUpScale = -(90) + 0.01;
		}

	}

		if ((glfwGetKey(87) == GLFW_PRESS))
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);

			forwDistance += SPEED;	
		}

		if ((glfwGetKey(83) == GLFW_PRESS))
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);

			forwDistance -= SPEED;
		}
		if ((glfwGetKey(68) == GLFW_PRESS))
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);

			leftDistance -= SPEED;
		}

		if ((glfwGetKey(65) == GLFW_PRESS))
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);

			leftDistance += SPEED;	
		}

		if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS)
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
			turnUpScale += 0.5;
			if (90 - turnUpScale < 0.01)
			{
				turnUpScale = 90 - 0.01;
			}
		}

		if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
			turnUpScale -= 0.5;
			if (turnUpScale + 90 < 0.01)
			{
				turnUpScale = - 90 + 0.01;
			}	
		}

		if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
			turnLeftScale += 0.5;	
		}

		if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
			turnLeftScale -= 0.5;	
		}

		this->setRotate(-turnUpScale, vec3(1, 0, 0));
		this->addRotate( turnLeftScale, vec3(0, 1, 0));
		
		float xincreasment = forwDistance*cos(turnUpScale / 180 * PI)*sin(turnLeftScale / 180 * PI) + leftDistance*cos(turnLeftScale / 180 * PI);
		float yincreasment = forwDistance*sin(turnUpScale / 180 * PI);
		float zincreasment = forwDistance*cos(turnUpScale / 180 * PI)*cos(turnLeftScale / 180 * PI) - leftDistance*sin(turnLeftScale / 180 * PI);

		this->setPos(this->getPos()+(vec3(xincreasment, yincreasment, zincreasment)));
		forwDistance = leftDistance = 0;
		lastx = newx;
		lasty = newy;
}

void Camera::calculateFrustum()
{
	//near pane point
	vec4 nvertex1 = vec4(nearPane*tanf(fov *aspect / 2 / 180 * PI), nearPane*tanf(fov / 2 / 180 * PI), nearPane, 1);
	vec4 nvertex2 = vec4(-nearPane*tanf(fov *aspect / 2 / 180 * PI), nearPane*tanf(fov / 2 / 180 * PI), nearPane, 1);
	vec4 nvertex3 = vec4(nearPane*tanf(fov *aspect / 2 / 180 * PI), -nearPane*tanf(fov / 2 / 180 * PI), nearPane, 1);
	vec4 nvertex4 = vec4(-nearPane*tanf(fov *aspect / 2 / 180 * PI), -nearPane*tanf(fov / 2 / 180 * PI), nearPane, 1);
	//far pane point
	vec4 fvertex1 = vec4(farPane*tanf(fov *aspect / 2 / 180 * PI), farPane*tanf(fov / 2 / 180 * PI), farPane, 1);
	vec4 fvertex2 = vec4(-farPane*tanf(fov *aspect / 2 / 180 * PI), farPane*tanf(fov / 2 / 180 * PI), farPane, 1);
	vec4 fvertex3 = vec4(farPane*tanf(fov *aspect / 2 / 180 * PI), -farPane*tanf(fov / 2 / 180 * PI), farPane, 1);
	vec4 fvertex4 = vec4(-farPane*tanf(fov *aspect / 2 / 180 * PI), -farPane*tanf(fov / 2 / 180 * PI), farPane, 1);

	vec4 vertex_data[] = { nvertex1, nvertex2, nvertex3, nvertex4, fvertex1, fvertex2, fvertex3, fvertex4 };
	frustum->setVertices(vertex_data);
	frustumCalculated = true;
}

