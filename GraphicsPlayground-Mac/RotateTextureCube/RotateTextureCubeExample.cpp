#include "stdafx.h"
#include "RotateTextureCubeExample.h"

#include "W_Common.h"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_ProgramManager.h"
#include "W_MaterialManager.h"

struct Vertex
{
	GLfloat x, y, z;
	GLfloat u,v;
};
static const Vertex cubeVertices[] = {
	// Front
	{ -0.5f, -0.5f, 0.5f, 0.0f,0.0f },
	{ -0.5f,  0.5f, 0.5f, 0.0f,1.0f },
	{ 0.5f,  0.5f, 0.5f, 1.0f,1.0f },
	{ 0.5f,  0.5f, 0.5f, 1.0f,1.0f},
	{ 0.5f, -0.5f, 0.5f, 1.0f,0.0f },
	{ -0.5f, -0.5f, 0.5f, 0.0f,0.0f },

	// Back
	{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f},
	{ -0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
	{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f},
	{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f},
	{ 0.5f, 0.5f, -0.5f, 0.0f, 0.0f},

	// Left
	{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f},
	{ -0.5f, 0.5f, 0.5f, 0.0f, 1.0f},
	{ -0.5f, -0.5f, 0.5f,  1.0f, 1.0f},
	{ -0.5f, -0.5f, 0.5f,  1.0f, 1.0f},
	{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f},
	{ -0.5f, 0.5f, -0.5f, 0.0f, 0.0f},

	// Right
	{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f},
	{ 0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
	{ 0.5f, -0.5f, 0.5f, 1.0f, 0.0f},
	{ 0.5f, 0.5f, 0.5f, 0.0f, 0.0f},

	// Top
	{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f},
	{ -0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
	{ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
	{ 0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
	{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f},
	{ -0.5f, 0.5f, 0.5f, 0.0f, 0.0f},

	// Bottom
	{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
	{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f},
	{ 0.5f, -0.5f, -0.5f, 1.0f, 1.0f},
	{ -0.5f, -0.5f, -0.5f, 1.0f, 0.0f},
	{ -0.5f, -0.5f, 0.5f, 0.0f, 0.0f},
};

static wolf::VertexBuffer* g_pVB = 0;
static wolf::VertexDeclaration* g_pDecl = 0;

static wolf::MaterialManager* g_Mat_Manager = 0;
static wolf::Material* mat = 0;
static wolf::Texture* tex = 0;

void RotateTextureCubeExample::Initialize() {
	wolf::ProgramManager* programManager = wolf::ProgramManager::Inst();
	wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
	wolf::TextureManager* textureManager = wolf::TextureManager::Inst();
	g_pVB = bufferManager->CreateVertexBuffer(cubeVertices, sizeof(cubeVertices));

	tex = textureManager->CreateTexture("/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/common/metal.tga");
	tex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
	tex->SetWrapMode(wolf::Texture::WM_Clamp, wolf::Texture::WM_Clamp);
	mat = g_Mat_Manager->CreateMaterial("texture_cube_material");
	mat->SetProgram("/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/RotateTextureCube.vsh", "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/RotateTextureCube.fsh");
	mat->SetDepthTest(true);
	mat->SetBlend(false);
	mat->SetTexture("tex", tex);

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();
}

void RotateTextureCubeExample::Render() {
	static float s_fRotation = 0;
	glm::mat4 mProj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	glm::mat4 mView = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 mWorld = glm::rotate(s_fRotation,  glm::vec3(0.0f, 1.0f, 0.0f));
	mWorld = mWorld * glm::rotate(s_fRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	s_fRotation += 0.01f;
	double time = glfwGetTime();

	// Bind Uniforms
	mat->SetUniform("projection", mProj);
	mat->SetUniform("view", mView);
	mat->SetUniform("world", mWorld);
	mat->SetUniform("time", time);

	// Set up source data
	g_pDecl->Bind();
	mat->Apply();

	glDrawArrays(GL_TRIANGLES,0, sizeof(cubeVertices) / sizeof(cubeVertices[0]));
}

void RotateTextureCubeExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){
    
}
