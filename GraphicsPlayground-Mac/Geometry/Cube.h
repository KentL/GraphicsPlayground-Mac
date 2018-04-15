#ifndef CUBE
#define CUBE
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#include <stdio.h>
#include <stdlib.h>
#ifndef __APPLE__
#include <GL/glew.h>
#endif
#include <GL/glfw.h>
#include "W_Common.h"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"

namespace Geometry{
class Cube
{
	
//public:void start(Vertex cubeVertices[])
//	{
//	static GLuint program = 0;
//	static GLuint vbo = 0;
//	static GLuint vao = 0;
//		glEnable(GL_DEPTH_TEST);
//
//		program = wolf::LoadShaders("data/week5/cube.vsh", "data/week5/cube.fsh");
//
//		glGenVertexArrays(1, &vao);
//		glBindVertexArray(vao);
//
//		glGenBuffers(1, &vbo);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6 * 3 * 2, cubeVertices, GL_STATIC_DRAW);
//		int iPosAttr = glGetAttribLocation(program, "a_position");
//		int iColAttr = glGetAttribLocation(program, "a_color");
//
//
//    }
//   

public:
	Cube();
	~Cube();
};
}
#endif
