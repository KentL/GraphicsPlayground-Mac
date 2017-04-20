#include "Node.h"
#include "glm/gtc/matrix_transform.hpp"

Node::Node(const string& name)
{
	this->name = name;
	hasParent = false;
	hasChild = false;
	myPosition =  vec3(0, 0, 0);
	myScale =  vec3(1, 1, 1);
	myRotAngles.push_back(0);
	myRotAxis.push_back(vec3(0, 1, 0));
	dirty = false;
	boundingRadius = 0;
	myTransform = glm::translate(myPosition) *glm::rotate(myRotAngles.at(0),vec3( myRotAxis.at(0).x, myRotAxis.at(0).y, myRotAxis.at(0).z)) *glm::scale(myScale);
}
Node::~Node()
{
	//delete parent;
}
void Node::addChild(Node* child)
{
	this->children.push_back(child);
	child->changeParFlag();
	child->setParent(this);
	hasChild = true;
}
void Node::setRotate(float angle, vec3 axis)//clear all the previous rotation and set a new one
{
	if (myRotAngles.size() != 0)
	{
		myRotAngles.clear();
		myRotAxis.clear();
	}
	myRotAngles.push_back(angle);
	myRotAxis.push_back(axis);
	dirty = true;
	
}
void Node::setPos(vec3 pos)
{
	myPosition = pos;
	dirty = true;
}
void Node::setScale(vec3 scale)
{
	myScale = scale;
	dirty = true;
}
void Node::rotate(float angle)
{
	myRotAngles.at(myRotAngles.size()-1) += angle;
	dirty = true;
}
void Node::scale(vec3 scale)
{
	myScale = vec3(myScale.x*scale.x, myScale.y*scale.y, myScale.z*scale.z);
	dirty = true;
}
void Node::translate(vec3 tran)
{
	myPosition += tran;
	dirty = true;
}
void Node::setRotateAxis(vec3 axis)
{
	myRotAxis.at(myRotAxis.size()-1) = axis;
	dirty = true;
}
void Node::addRotate(float angle, vec3 axis)
{
	myRotAngles.push_back(angle);
	myRotAxis.push_back(axis);
	dirty = true;
}
mat4 Node::getTransform()
{
	if (dirty)
	{	
		for (int i = 0; i < myRotAngles.size(); i++)
		{
			if (i == 0)
			{
                myTransform = glm::rotate(glm::radians(myRotAngles.at(i)) , vec3(myRotAxis.at(i).x, myRotAxis.at(i).y, myRotAxis.at(i).z));
			}
			else
			{
				myTransform = glm::rotate(glm::radians(myRotAngles.at(i)) , vec3(myRotAxis.at(i).x, myRotAxis.at(i).y, myRotAxis.at(i).z))*myTransform;
			}
		}
		myTransform = glm::translate(myPosition)*myTransform*glm::scale(myScale);
		dirty = false;
	}
	return myTransform;
}

mat4 Node::getRotationMatrix()
{
	for (int i = 0; i < myRotAngles.size(); i++)
	{
		if (i == 0)
		{
			myRotationMatrix = glm::rotate(glm::radians(myRotAngles.at(i)),vec3( myRotAxis.at(i).x, myRotAxis.at(i).y, myRotAxis.at(i).z));
		}
		else
		{
			myRotationMatrix = glm::rotate(glm::radians(myRotAngles.at(i)),vec3( myRotAxis.at(i).x, myRotAxis.at(i).y, myRotAxis.at(i).z)) * myRotationMatrix;
		}
	}
	return myRotationMatrix;
}
vec3 Node::getPos()
{
	return myPosition;
}

mat4 Node::getWorldTransform()
{
	if (hasParent)
	{
		return (parent->getWorldTransform())*getTransform();
	}
	return getTransform();
}

void Node::changeParFlag()
{
	hasParent = true;
}

void Node::setDirtyFlag(bool flag)
{
	dirty = flag;
}

void Node::setParent(Node* parent)
{
	this->parent = parent;
}

void Node::render()
{
	printf("This is the base class's method should not be called");
}

void Node::update()
{
	if (hasChild)
	{
		for (int  i = 0; i < children.size(); i++)
		{
			children.at(i)->update();
			float distance = calculateDistance(children.at(i), this);
            this->boundingRadius = std::max(this->boundingRadius, distance + children.at(i)->boundingRadius);
		}
	}
	else if (hasParent)
	{
		float distance = calculateDistance(parent, this);
        parent->boundingRadius = std::max(distance, parent->boundingRadius);
	}

}

float Node::calculateDistance( Node* node1,  Node* node2)
{
	int node1x = node1->getPos().x;
	int node1y = node1->getPos().y;
	int node1z = node1->getPos().z;
	int node2x = node2->getPos().x;
	int node2y = node2->getPos().y;
	int node2z = node2->getPos().z;

	
	float distance = sqrtf(pow((node1x - node2x), 2.0) + pow((node1y - node2y), 2.0) + pow((node1z - node2z), 2.0));
	return distance;
	
}

float Node::getBoundingRadius()
{
	return boundingRadius;
}
