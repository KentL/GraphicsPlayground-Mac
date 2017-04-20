//========================================================================
// Week 5 - Buffers and Attributes
//
// Example 4: Rendering a cube, using our beginnings of Wolf
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#define TIME_ELAPSE_SPEED 10
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
#include "SkyBox.h"
#include "examples.h"

#pragma region define variables

static Camera* mainCamera;
static CityModeller* cityModeller;
static SkyBox* skybox;
int key_f_pressed_counter = 0;//record how many times key "F" is pressed to change the fov of maincamera
int key_b_pressed_counter = 0;//record how many times key "B" is pressed to turn skybox-rendering on and off
float last_time_key_f_pressed = 0;//Record the last time that key 'F' is pressed to change the fov of mainCamera
float last_time_key_b_pressed = 0;//Record the last time that key 'B' is pressed to turn skybox-rendering on and off
static bool key_r_pressed = false;//Indicate if key "R" is pressed to change the city layout

#pragma endregion

void Init(bool first_time)
{
	//If it's the first time to init the scene,do these preparation jobs,otherwise just create new city
	if (first_time)
	{
		//Setup Camera
		mainCamera = new Camera();
		mainCamera->setPos(vec3(0, 30, -15));
		mainCamera->setFOV(45);
		mainCamera->setNear(0.1f);
		mainCamera->setFar(30000.0f);
		mainCamera->setAspect(1280.0f / 720.0f);

		cityModeller = new CityModeller();
		cityModeller->SetTexture("data/assignment2/texturemap2.tga");
		cityModeller->SetProgram("data/assignment2/city_model.vsh", "data/assignment2/city_model.fsh");
		cityModeller->SetCamera(mainCamera);

		//Initialize SkyBox properties
		string textureNames[] = { "data/assignment2/skybox/skybox_texture_posX.tga", "data/assignment2/skybox/skybox_texture_negX.tga",
								"data/assignment2/skybox/skybox_texture_posY.tga", "data/assignment2/skybox/skybox_texture_negY.tga",
								"data/assignment2/skybox/skybox_texture_posZ.tga", "data/assignment2/skybox/skybox_texture_negZ.tga" };
		skybox = new SkyBox();
		skybox->SetCamera(mainCamera);
		skybox->SetPositon(vec3(0, 0, 0));
		skybox->SetProgram("data/assignment2/skybox.vsh", "data/assignment2/skybox.fsh");
		skybox->SetScale(vec3(20, 20, 20));
		skybox->SetTexture(textureNames);
		skybox->PrepareData();
		
	}

	cityModeller->generateCityLayoutData(first_time);
	mainCamera->SetAABBColliders(cityModeller->GetAABBColliders());
}

void Render()
{
	//press 'F' to change camera focus lens
	if (glfwGetKey(70) == GLFW_PRESS&&glfwGetTime()-last_time_key_f_pressed>0.5)
	{
		last_time_key_f_pressed = glfwGetTime();
		key_f_pressed_counter++;
		switch (key_f_pressed_counter % 3)
		{
		case 0:
			mainCamera->setFOV(45);
			break;
		case 1:
			mainCamera->setFOV(30);
			break;
		case 2:
			mainCamera->setFOV(10);
			break;
		}
	}
	
	//press 'R' to change the layout
	if (glfwGetKey(82) == GLFW_PRESS&&!key_r_pressed)
	{
		Init(false);
		key_r_pressed = true;	
	}
	else
	{
		key_r_pressed = false;
	}

	mainCamera->cameraMove();

	//Press 'B' to change skybox-rendering flag
	if (glfwGetKey(66) == GLFW_PRESS&&glfwGetTime() - last_time_key_b_pressed > 0.5)
	{
		key_b_pressed_counter = (key_b_pressed_counter + 1) % 2;
		last_time_key_b_pressed = glfwGetTime();
	}
	

	if (key_b_pressed_counter==1)
	{
		skybox->Render();
	}

	cityModeller->Render();
}


