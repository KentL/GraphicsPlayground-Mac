#ifndef STRUCT
#define STRUCT
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include "W_Common.h"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"

using namespace std;
using namespace glm;
struct Vertex1
{
	GLfloat x, y, z;
	GLubyte r, g, b, a;
};



struct Vertex2
{
	GLfloat x, y, z;
	GLfloat u, v;
	GLfloat normalx, normaly, normalz;
};

struct Vertex3
{
	GLfloat x, y, z;
};

struct building
{
	GLfloat length,width, height ;
	glm::vec2 gridCoordinate;//number in grids

};

struct road
{
	GLint beginGridRow,beginGridColumn, endGridRow,endGridColumn;	
};

struct singlegrid
{
	GLint row, column;
};

static  const Vertex2 plane[] = {

		{ -5200.0f , -3.0f, 17000.0f , 0.5, 0.02, 0, 1, 0 },
		{ 17000.0f , -3.0f, 17000.0f , 0.6, 0.02, 0, 1, 0 },
		{ 17000.0f , -3.0f, -5200.0f , 0.6, 0.18, 0, 1, 0 },
		{ 17000.0f , -3.0f, -5200.0f , 0.6, 0.18, 0, 1, 0 },
		{ -5200.0f , -3.0f, 17000.0f , 0.5, 0.02, 0, 1, 0 },
		{ -5200.0f , -3.0f, -5200.0f , 0.5, 0.18, 0, 1, 0 },

};

struct texture_corner_uv
{
	vec2 top_left;
	vec2 top_right;
	vec2 bottom_left;
	vec2 bottom_right;
};

struct texture_category
{
	string name;
	int element_amount;
	texture_corner_uv* corner_uv;
};


#endif
