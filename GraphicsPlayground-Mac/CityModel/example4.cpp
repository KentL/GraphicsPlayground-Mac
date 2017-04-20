//========================================================================
// Week 5 - Buffers and Attributes
//
// Example 4: Rendering a cube, using our beginnings of Wolf
//========================================================================
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
#include "W_MaterialManager.h"
#include "CityModeller.h"
#include "W_Texture.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include <vector>
#include <struct.h>
#include <SurfaceMaterial.h>




static wolf::VertexBuffer* g_pVB1 = 0;
static wolf::VertexDeclaration* g_pDecl = 0;
static wolf::Program* g_pProgram1 = 0;

static wolf::MaterialManager* g_Mat_Manager = 0;
static wolf::Material* mat = 0;
static wolf::Texture* tex_map = 0;

static SurfaceMaterial* g_maskSurface;
static DirectionalLight* g_light;

float angle = 0;

static Camera* mainCamera;
static CityModeller* cityModeller;


void InitExample4(bool first_time)
{
	if (first_time)
	{
		mainCamera = new Camera();
		mainCamera->setPos(vec3(0, 0, -15));
		mainCamera->setFOV(45);
		mainCamera->setNear(0.1f);
		mainCamera->setFar(10000.0f);
		mainCamera->setAspect(1280.0f / 720.0f);

		cityModeller = new CityModeller();

		tex_map = wolf::TextureManager::CreateTexture("data/assignment2/texturemap2.tga");
		tex_map->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
		tex_map->SetWrapMode(wolf::Texture::WM_Clamp, wolf::Texture::WM_Clamp);
		mat = g_Mat_Manager->CreateMaterial("city_model_material");
		mat->SetProgram("data/assignment2/city_model.vsh", "data/assignment2/city_model.fsh");
		mat->SetDepthTest(true);
		mat->SetBlend(false);
		mat->SetTexture("tex", tex_map);

		g_maskSurface = new SurfaceMaterial();
		g_maskSurface->setDiffuse( wolf::Color4(1, 1, 0.8, 1));
		g_maskSurface->setAmbient(wolf::Color4(0.5, 0.5, 0.5, 1));
		g_maskSurface->setSpecular(wolf::Color4(1, 1, 1, 200));

		// Initialize the light parameters
		g_light = new DirectionalLight();
		g_light->setDiffuse(wolf::Color4(1.0, 1.0, 0.6, 1));
		g_light->setAmbient(wolf::Color4(0.5, 0.5, 0.5, 1));
		g_light->setSpecular(wolf::Color4(0.2, 0.2, 0.1, 1));
	}

	cityModeller->generateCityLayoutData(first_time);

	g_pVB1 = wolf::BufferManager::CreateVertexBuffer(&cityModeller->getBuffer()->at(0), sizeof(Vertex2) *(cityModeller->getBuffer()->size()));

	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
	g_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB1);
	g_pDecl->End();
	
	
}

static float s_fRotation = 0;
static bool keypressed = false;

void RenderExample4()
{
	//press 'r' to change the layout
	if (glfwGetKey(82) == GLFW_PRESS&&!keypressed)
	{
		InitExample4(false);
		keypressed = true;	
	}
	else
	{
		keypressed = false;
	}

	mainCamera->cameraMove();

	angle += 0.01;
	
	g_light->rotate(angle);
	
	//make the light's intensity decrease gradually
	float dir_light_vertical_direction = g_light->getDirection().y;
	float dir_light_decrease_factor = dir_light_vertical_direction;
	if ( dir_light_vertical_direction< 0)
	{
		g_light->setDiffuse(wolf::Color4(-1.0*dir_light_decrease_factor, -1.0*dir_light_decrease_factor, -0.6*dir_light_decrease_factor, 1));
		g_light->setSpecular(wolf::Color4(-0.2*dir_light_decrease_factor, -0.2*dir_light_decrease_factor, -0.1*dir_light_decrease_factor, 1));
	}
	else
	{
		g_light->setDiffuse(wolf::Color4(0.0, 0.0, 0.0, 1));
		g_light->setSpecular(wolf::Color4(0.0, 0.0, 0.0, 1));
	}

	g_light->setDirection( glm::vec3(0.0f, sinf(angle), cosf(angle)));

	glm::mat4 mProj = mainCamera->getProjectionMatrix();
	glm::mat4 mView = mainCamera->getViewMatrix();
	glm::mat4 mWorld = mProj*mView;

 
	// Bind Uniforms
	mat->SetUniform("WorldViewProj", mWorld);
	mat->SetUniform("ViewDir", glm::vec3(mainCamera->getViewDirection()));
    
	// Set the light parameters
	mat->SetUniform("LightAmbient", g_light->getAmbient());
	mat->SetUniform("LightDiffuse", g_light->getDiffuse());
	mat->SetUniform("LightSpecular", g_light->getSpecular());
	mat->SetUniform("LightDir", g_light->getDirection());
	
	// Set the surface parameters
	mat->SetUniform("MatAmbient", g_maskSurface->getAmbient());
	mat->SetUniform("MatDiffuse", g_maskSurface->getDiffuse());
	mat->SetUniform("MatSpecular", g_maskSurface->getSpecular());
	
	g_pDecl->Bind();
	mat->Apply();
	
	glDrawArrays(GL_TRIANGLES, 0, cityModeller->getBuffer()->size());

}


