#include "stdafx.h"
#include "RotateCubeExample.h"
#include "W_Common.h"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"

struct Vertex
{
	GLfloat x, y,z;
	GLubyte r, g, b, a;
};
static const Vertex cubeVertices[] = {
	// Front
	{ -0.5f, -0.5f, 0.5f, 255, 0, 0, 255 },
	{ -0.5f,  0.5f, 0.5f, 255, 0, 0, 255 },
	{ 0.5f,  0.5f, 0.5f, 255, 0, 0, 255 },
	{ 0.5f,  0.5f, 0.5f, 255, 0, 0, 255 },
	{ 0.5f, -0.5f, 0.5f, 255, 0, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 255, 0, 0, 255 },

	// Back
	{ 0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{ 0.5f, -0.5f,-0.5f, 128, 0, 0, 255 },
	{ 0.5f,  0.5f,-0.5f, 128, 0, 0, 255 },

	// Left
	{ -0.5f,  0.5f,-0.5f, 0, 255, 0, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 255, 0, 255 },
	{ -0.5f, -0.5f,-0.5f, 0, 255, 0, 255 },
	{ -0.5f,  0.5f,-0.5f, 0, 255, 0, 255 },

	// Right
	{ 0.5f,  0.5f, 0.5f, 0, 128, 0, 255 },
	{ 0.5f,  0.5f,-0.5f, 0, 128, 0, 255 },
	{ 0.5f, -0.5f,-0.5f, 0, 128, 0, 255 },
	{ 0.5f, -0.5f,-0.5f, 0, 128, 0, 255 },
	{ 0.5f, -0.5f, 0.5f, 0, 128, 0, 255 },
	{ 0.5f,  0.5f, 0.5f, 0, 128, 0, 255 },

	// Top
	{ -0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },
	{ -0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{ 0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{ 0.5f,  0.5f,-0.5f, 0, 0, 255, 255 },
	{ 0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },
	{ -0.5f,  0.5f, 0.5f, 0, 0, 255, 255 },

	// Bottom
	{ -0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
	{ 0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
	{ 0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ 0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ -0.5f, -0.5f,-0.5f, 0, 0, 128, 255 },
	{ -0.5f, -0.5f, 0.5f, 0, 0, 128, 255 },
};

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;

void RotateCubeExample::HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos) {
    
}

void RotateCubeExample::Initialize() {
	glEnable(GL_DEPTH_TEST);
	wolf::ProgramManager* programManager = wolf::ProgramManager::Inst();
	wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
	g_pProgram = programManager->CreateProgram("/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/RotateCube.vsh", "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/RotateCube.fsh");
	g_pVB = bufferManager->CreateVertexBuffer(cubeVertices, sizeof(cubeVertices));

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_UByte);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();
}

void RotateCubeExample::Render() {
	static float s_fRotation = 0;
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mWorld = glm::rotate(s_fRotation, glm::vec3(0.0f, 1.0f, 0.0f));
	mWorld = mWorld * glm::rotate(s_fRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	s_fRotation += 0.01f;

	// Use shader program.
	g_pProgram->Bind();

	// Bind Uniforms
	g_pProgram->SetUniform("projection", mProj);
	g_pProgram->SetUniform("view", mView);
	g_pProgram->SetUniform("world", mWorld);

	// Set up source data
	g_pDecl->Bind();
    glEnable(GL_CLIP_DISTANCE0);
    glm::vec4 PlaneEquation = glm::vec4(1, -1, 1, 0);

    glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices)/sizeof(cubeVertices[0]));
}

void RotateCubeExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){}

