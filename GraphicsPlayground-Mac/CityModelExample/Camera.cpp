#include "stdafx.h"
#include "W_Common.h"
#include "Camera.h"
#include "AABBCollider.h"
#include "SphereCollider.h"
#include "CollisionDetector.h"
#include "CollisionHelper.h"
#include "Triangle.h"
#define SPEED 2
#define COLLIDER_RADIUS 1

using namespace Geometry;

Camera::Camera() 
{
	frustum = new FrustumNode();
	addChild(frustum);
	turnLeftScale = turnUpScale = 0;
	leftDistance = forwDistance = 0;
	c_lasttime_clicked = glfwGetTime(); 
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
	viewMatrix = glm::lookAt(this->getPos(), this->getPos() + vec3(lookatPoint), vec3(up.x,up.y,up.z));
	
	return viewMatrix;
}
void Camera::setUpDirection(vec4 up){
    this->up=up;
}
vec4 Camera::getViewDirection()
{
	return lookatPoint;
}

mat4 Camera::getProjectionMatrix()
{
    projectionMatrix=glm::perspective(glm::radians(fov), aspect, nearPane, farPane);
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
void Camera::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_C &(glfwGetTime() -c_lasttime_clicked)>0.5)
    {
        collisionSwitch = (collisionSwitch + 1) % 2;
        c_lasttime_clicked = glfwGetTime();
    }
}
void Camera::setMouseSensitivity(int sensitivity){
    this->mouseSensitivity  = sensitivity;
}
void Camera::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos){
    
}
void Camera::setViewDirection(vec3 viewDirection){
    this->lookatPoint.x = viewDirection.x;
    this->lookatPoint.y = viewDirection.y;
    this->lookatPoint.z = viewDirection.z;
    this->lookatPoint.w = 1;
}
void Camera::detectInput(){
    if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)
    {
        forwDistance += SPEED;
    }
    
    if (glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)
    {
        
        forwDistance -= SPEED;
    }
    if (glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)
    {
        leftDistance -= SPEED;
    }
    
    if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)
    {
        leftDistance += SPEED;
    }
    
    if (glfwGetKey(window, GLFW_KEY_UP)==GLFW_PRESS)
    {
        turnUpScale += 0.5;
        if (90 - turnUpScale < 0.01)
        {
            turnUpScale = 90 - 0.01;
        }
    }
    
    if (glfwGetKey(window, GLFW_KEY_DOWN)==GLFW_PRESS)
    {
        turnUpScale -= 0.5;
        if (turnUpScale + 90 < 0.01)
        {
            turnUpScale = - 90 + 0.01;
        }
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS)
    {
        turnLeftScale += 0.5;
    }
    
    if (glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS)
    {
        turnLeftScale -= 0.5;
    }
    
    
    glfwGetCursorPos(window, &newx, &newy);
    if (newx > 1200 || newx < 10 || newy < 10 || newy>700)
    {
        glfwSetCursorPos(window, 600, 350);
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
        turnLeftScale = turnLeftScale - (newx - lastx) / mouseSensitivity;
        turnUpScale = turnUpScale - (newy - lasty) / mouseSensitivity;
        
        
        if (90 - turnUpScale < 0.01)
        {
            turnUpScale = 90 - 0.01;
        }
        if (turnUpScale + 90 < 0.01)
        {
            turnUpScale = -(90) + 0.01;
        }
        
    }
}
void Camera::cameraMove()
{
    detectInput();
    this->setRotate(-turnUpScale, vec3(1, 0, 0));
    this->addRotate( turnLeftScale, vec3(0, 1, 0));
    
    float xincreasment = forwDistance*cos(turnUpScale / 180 * PI)*sin(turnLeftScale / 180 * PI) + leftDistance*cos(turnLeftScale / 180 * PI);
    double a = sin(turnUpScale / 180 * PI);
    
    float yincreasment = forwDistance*sin(turnUpScale / 180 * PI);
    
    double b = cos(turnUpScale / 180 * PI);
    double c = cos(turnLeftScale / 180 * PI);

    float zincreasment = forwDistance*cos(turnUpScale / 180 * PI)*cos(turnLeftScale / 180 * PI) - leftDistance*sin(turnLeftScale / 180 * PI);
    
    
    if (collisionSwitch==1)
    {
        CollideAndSlide(vec3(xincreasment, yincreasment, zincreasment));
    }
    else
    {
        myPosition += vec3(xincreasment, yincreasment, zincreasment);
    }
    lookatPoint = this->getRotationMatrix()*vec4(0, 0, 1, 1);
    forwDistance = 0;
    leftDistance = 0;
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

void Camera::SetAABBColliders(vector<Colliders::AABBCollider*>* colliders)
{
	this->aabbColliders = colliders;
}

void Camera::CheckCollision(CollisionPackage* collisionPackage)
{
	double radius = 10*collisionPackage->eRadius.x;
	vec3 pos = collisionPackage->basePoint;
	SphereCollider* sphere = new SphereCollider(pos, radius);
	vector<AABBCollider*> collided_aabbs = vector<AABBCollider*>();
	for (int i = 0; i < aabbColliders->size(); i++)
	{
		if (CollisionDetector::Does_AABB_Sphere_Collide(aabbColliders->at(i),sphere))
		{
			collided_aabbs.push_back(aabbColliders->at(i));
		}
	}
	for (int i = 0; i < collided_aabbs.size(); i++)
	{
		Geometry::Triangle triangles[12];
		ConstructTriangleFromAABB(collided_aabbs.at(i), triangles);
		for (int j = 0; j < 12; j++)
		{
			CheckTriangle(collisionPackage, triangles[j].vertex1, triangles[j].vectex2, triangles[j].vectex3,triangles[j].normal);
		}
	}

	delete sphere;
}

vec3 Camera::CollideWithWorld(const vec3& pos, const vec3& vel)
{
	// All hard-coded distances in this function is
	// scaled to fit the setting above..
	float unitScale = unitsPerMeter / 100.0f;
	float veryCloseDistance = 0.005f * unitScale;
	// do we need to worry?
	if (collisionRecursionDepth>5)
		return pos;
	CollisionPackage* collisionPackage = new CollisionPackage();
	// Ok, we need to worry:
	collisionPackage->velocity = vel;
	collisionPackage->normalizedVelocity = glm::normalize(vel);
	collisionPackage->basePoint = pos;
	collisionPackage->foundCollision = false;
	collisionPackage->eRadius = vec3(1, 1, 1);
	// Check for collision (calls the collision routines)
	// Application specific!!
	CheckCollision(collisionPackage);
	// If no collision we just move along the velocity
	if (collisionPackage->foundCollision == false) {
		return pos + vel;
	}
	// *** Collision occured ***
	// The original destination point
	vec3 destinationPoint = pos + vel;
	vec3 newBasePoint = pos;
	// only update if we are not already very close
	// and if so we only move very close to intersection..not
	// to the exact spot.
	if (collisionPackage->nearestDistance >= veryCloseDistance)
	{
		vec3 v = vel;
		SetLength(v,collisionPackage->nearestDistance - veryCloseDistance);
		newBasePoint = collisionPackage->basePoint + v;
		// Adjust polygon intersection point (so sliding
		// plane will be unaffected by the fact that we
		// move slightly less than collision tells us)
		v = glm::normalize(v);
		collisionPackage->intersectionPoint -= veryCloseDistance * v;
	}
	// Determine the sliding plane
	vec3 slidePlaneOrigin = collisionPackage->intersectionPoint;
	vec3 slidePlaneNormal = newBasePoint - collisionPackage->intersectionPoint;
	slidePlaneNormal=normalize(slidePlaneNormal);
	Plane slidingPlane(slidePlaneOrigin, slidePlaneNormal);
	// Again, sorry about formatting.. but look carefully ;)
	double sdis = slidingPlane.signedDistanceTo(destinationPoint);
	vec3 newDestinationPoint = destinationPoint - vec3(sdis,sdis,sdis)*slidePlaneNormal;
	// Generate the slide vector, which will become our new
	// velocity vector for the next iteration
	vec3 newVelocityVector = newDestinationPoint - collisionPackage->intersectionPoint;
	// Recurse:
	// dont recurse if the new velocity is very small
	if (newVelocityVector.length() < veryCloseDistance) {
		return newBasePoint;
	}
	collisionRecursionDepth++;

	delete collisionPackage;
	return CollideWithWorld(newBasePoint, newVelocityVector);
}
void Camera::setWindow(GLFWwindow *window){
    this->window=window;
}
void Camera::CollideAndSlide(const vec3& vel)
{
	CollisionPackage* collisionPackage = new CollisionPackage();
	// Do collision detection:
	collisionPackage->R3Position = this->myPosition;
	collisionPackage->R3Velocity = vel;
	collisionPackage->eRadius = vec3(1, 1, 1);
	// calculate position and velocity in eSpace
	vec3 eSpacePosition = collisionPackage->R3Position;// / collisionPackage->eRadius;
	vec3 eSpaceVelocity = collisionPackage->R3Velocity;// / collisionPackage->eRadius;

	// Iterate until we have our final position.
	collisionRecursionDepth = 0;
	vec3 finalPosition = CollideWithWorld(eSpacePosition, eSpaceVelocity);
	// Convert final result back to R3:
	finalPosition = finalPosition*collisionPackage->eRadius;
	// Move the entity (application specific function)
	myPosition = finalPosition;
}
