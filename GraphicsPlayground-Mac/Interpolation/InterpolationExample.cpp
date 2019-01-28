#include "stdafx.h"
#include "InterpolationExample.h"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"

struct Vertex
{
	GLfloat x, y;
	GLubyte r, g, b, a;
};
static const Vertex squareVertices[] = {
	{100.0f, 100.0f,	255,255, 0, 255}, //yellow
	{100.0f, 620.0f,	0,255, 0, 255}, //green
	{1180.0f, 620.0f,	255,0, 0, 255 }, //red

	{1180.0f, 620.0f,	0,0, 255, 255, }, //blue
	{1180.0f, 100.0f,	255,0, 255, 255}, //magenta
	{100.0f, 100.0f,	0,255, 255, 255} //cyan
};


static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram = 0;

void InterpolationExample::HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos) {
    
}

void InterpolationExample::Initialize() {
	wolf::ProgramManager* programManager = wolf::ProgramManager::Inst();
	wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
	g_pProgram = programManager->CreateProgram("/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/interpolation.vsh", "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/interpolation.fsh");
	g_pVB = bufferManager->CreateVertexBuffer(squareVertices, sizeof(squareVertices) );

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_Color, 4, wolf::CT_UByte);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();
}

void InterpolationExample::Render() {
	glm::mat4 mProj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, 0.0f, 1000.0f);
	g_pProgram->Bind();
	g_pProgram->SetUniform("projection", mProj);
	g_pDecl->Bind();

	glDrawArrays(GL_TRIANGLES, 0, sizeof(squareVertices)/sizeof(squareVertices[0]));

}

void InterpolationExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){}
