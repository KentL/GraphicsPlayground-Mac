#ifndef PARTICLESTRUCT
#define PARTICLESTRUCT
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

#include "W_Common.h"

class Emitter;
class Affector;

using namespace std;
using namespace glm;

struct Vertex
{
	GLfloat x, y, z;
	GLfloat r, g, b, a;
	GLfloat u, v;
};

struct SceneScope
{
	GLfloat xmax, xmin;
	GLfloat ymax, ymin;
	GLfloat zmax, zmin;
};

struct pane
{
	float a, b, c, d;
};

struct quadTreeVertex
{
	GLfloat x, y, z;
	GLfloat r, g, b, a;
};

struct particle
{
	float lifetime;
	float fade;
	float age;
	float size;
	vec4 color;
	vec3 velocity;
	vec3 position;
	Emitter* m_emitter;
	vector<Affector*> m_pAffector;
	particle* prev;
	particle* next;
};


enum spawn_property_name
{
	velocity, color, size, fade, lifetime,box_min,box_max
};
enum spawn_property_type
{
	randomType,constantType
};
struct spawn_property
{
	spawn_property_name  name;
	spawn_property_type type;
	string value;
	string max;
	string min;
};



#endif
