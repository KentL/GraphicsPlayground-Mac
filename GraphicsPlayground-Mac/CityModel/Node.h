#ifndef NODE
#define NODE
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>

#include "W_Common.h"

using namespace std;
using namespace glm;

class Node
{
protected:
	string name;	
	vector<Node*> children;
	mat4 myTransform;
	vec3 myPosition;
	mat4 myRotationMatrix;
	vec3 myScale;
	vector<vec3> myRotAxis;
	Node* parent;
	vector<float> myRotAngles;
	bool dirty;
	bool hasParent;
	bool hasChild;
	void changeParFlag();
	void setParent(Node* parent);
	float calculateDistance( Node* node1,  Node* node2);
	

protected:
	float boundingRadius;
	
public:
	Node(const string& name="");
	~Node();
	void addChild(Node* child);

	void setRotate(float angle,vec3 rotate);//clear all the previous rotation and set a new one
	void addRotate(float angle, vec3 rotate);
	void setPos(vec3 pos);
	void setScale(vec3 scale);
	void setRotateAxis(vec3 axis);
	void setDirtyFlag(bool flag);

	mat4 getTransform();
	mat4 getWorldTransform();
	mat4 getRotationMatrix();
	vec3 getPos();
	float getBoundingRadius();

	void rotate(float angle);
	void scale(vec3 scale);
	void translate(vec3 tran);

	
	
	void update();
	virtual void render();


		
};
#endif
