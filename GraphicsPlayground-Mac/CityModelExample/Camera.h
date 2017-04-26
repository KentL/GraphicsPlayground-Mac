#ifndef CAMERA
#define CAMERA
#include "stdafx.h"
#include "W_Common.h"
#include "Node.h"
#include "Frustum.h"
#include "W_VertexDeclaration.h"
#include "AABBCollider.h"
#include "CollisionPackage.h"
#include "KeyboardInputHandler.hpp"
#include "MouseInputHandler.hpp"


using namespace std;
using namespace glm;
using namespace Geometry;

class Camera:public Node,public KeyboardInputHandler,public MouseInputHandler
{
private:
	FrustumNode* frustum;
	float fov;
	float farPane, nearPane;
	float aspect;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	vec4* vertices;
	vec4 lookatPoint;
	bool frustumCalculated;
	vector<Colliders::AABBCollider*>* aabbColliders;

	//camera movement parameters

	float turnLeftScale, turnUpScale;
	float leftDistance, forwDistance;
	float newx, newy, lastx, lasty;
	bool isfirsttime;

	//Collision Detection Part:
	// Set this to match application scale..
	const float unitsPerMeter = 1000.0f;
	int collisionRecursionDepth;
	int collisionSwitch=0;

	//Time recorder
	double c_lasttime_clicked;
    int mouseSensitivity = 1;

public:
	Camera();
	~Camera();
	void setPos(vec3 pos);
	void setFOV(float fov);
	void setFar(float far);
	void setNear(float near);
	void setAspect(float aspect);
	void SetAABBColliders(vector<Colliders::AABBCollider*>* aabbColliders);

	float getFar();
	float getNear();
	float getFOV();
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	FrustumNode getFrustum();
	void calculateFrustum();
	vec4 getViewDirection();

	void cameraMove();
	vec3 CollideWithWorld(const vec3& pos, const vec3& vel);
	void CheckCollision(CollisionPackage* collisionPacket);
	void CollideAndSlide(const vec3& vel);
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos);
    
    void setMouseSensitivity(int sensitivity);
};

#endif
