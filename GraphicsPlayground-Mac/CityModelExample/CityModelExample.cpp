//========================================================================
// Week 5 - Buffers and Attributes
//
// Example 4: Rendering a cube, using our beginnings of Wolf
//========================================================================
#define GLFW_INCLUDE_GL3
#define GLFW_NO_GLU
#define TIME_ELAPSE_SPEED 10
#include "stdafx.h"
#include "CityModelExample.h"

void CityModelExample::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos){
    mainCamera->HandleCursorPositionChange(window, newXPos, newYPos);
}
void CityModelExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){
    //press 'F' to change camera focus lens
    if (key == GLFW_KEY_F &&glfwGetTime()-last_time_key_f_pressed>0.5)
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
    if (key == GLFW_KEY_R)
    {
        RebuildCityModel();
    }

    //Press 'B' to change skybox-rendering flag
    if (key == GLFW_KEY_B && glfwGetTime() - last_time_key_b_pressed > 0.5)
    {
        key_b_pressed_counter = (key_b_pressed_counter + 1) % 2;
        last_time_key_b_pressed = glfwGetTime();
    }
    mainCamera->HandleKeyInput(window, key, scancode, action, mods);
}
void CityModelExample::Initialize()
{
    
        string pictureDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/citymodel/";
        string shaderDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/";
		//Setup Camera
		mainCamera = new Camera();
		mainCamera->setPos(vec3(0, 30, -15));
		mainCamera->setFOV(45);
		mainCamera->setNear(0.1f);
		mainCamera->setFar(30000.0f);
		mainCamera->setAspect(1280.0f / 720.0f);

		cityModeller = new CityModeller();
		cityModeller->SetTexture(pictureDir+"CityModelTextureMap.tga");
		cityModeller->SetProgram(shaderDir+"city_model.vsh", shaderDir+"city_model.fsh");
		cityModeller->SetCamera(mainCamera);

		//Initialize SkyBox properties
		string textureNames[] = { pictureDir+"skybox/skybox_texture_posX.tga", pictureDir+"skybox/skybox_texture_negX.tga",
								pictureDir+"skybox/skybox_texture_posY.tga", pictureDir+"skybox/skybox_texture_negY.tga",
								pictureDir+"skybox/skybox_texture_posZ.tga", pictureDir+"skybox/skybox_texture_negZ.tga" };
		skybox = new SkyBox();
		skybox->SetCamera(mainCamera);
		skybox->SetPositon(vec3(0, 0, 0));
		skybox->SetProgram(shaderDir+"skybox.vsh", shaderDir+"skybox.fsh");
		skybox->SetScale(vec3(20, 20, 20));
		skybox->SetTexture(textureNames);
		skybox->PrepareData();
    
    RebuildCityModel();

}
void CityModelExample::RebuildCityModel(){
    cityModeller->generateCityLayoutData();
    mainCamera->SetAABBColliders(cityModeller->GetAABBColliders());
}
void CityModelExample::Render()
{
    mainCamera->cameraMove();

	if (key_b_pressed_counter==1)
	{
		skybox->Render();
	}

	cityModeller->Render();
}


