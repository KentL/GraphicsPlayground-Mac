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
                mainCamera->setFOV(45.0f);
                break;
            case 1:
                mainCamera->setFOV(30.0f);
                break;
            case 2:
                mainCamera->setFOV(10.0f);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    string pictureDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/citymodel/";
    string shaderDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/";
    //Setup Camera
    mainCamera = new Camera();
    mainCamera->setPos(vec3(0, 0, 0));
    mainCamera->setFOV(45.0f);
    mainCamera->setNear(0.1f);
    mainCamera->setFar(10000.0f);
    mainCamera->setAspect(640.0f / 480.0f);
    mainCamera->setWindow(window);
    
    cityModeller = new CityModeller();
    cityModeller->SetTexture(pictureDir+"CityModelTextureMap2.png");
    cityModeller->SetProgram(shaderDir+"city_model.vsh", shaderDir+"city_model.fsh");
    cityModeller->SetCamera(mainCamera);
    cityModeller->SetWindow(window);
    
    //Initialize SkyBox properties
    string textureNames[] = { pictureDir+"skybox-png/skybox_texture_posX.png", pictureDir+"skybox-png/skybox_texture_negX.png",
								pictureDir+"skybox-png/skybox_texture_posY.png", pictureDir+"skybox-png/skybox_texture_negY.png",
								pictureDir+"skybox-png/skybox_texture_posZ.png", pictureDir+"skybox-png/skybox_texture_negZ.png" };
    
    skybox = new SkyBox();
    skybox->SetCamera(mainCamera);
    skybox->SetWindow(window);
    skybox->SetPositon(vec3(0, 5, 0));
    skybox->SetProgram(shaderDir+"skybox.vsh", shaderDir+"skybox.fsh");
    skybox->SetScale(vec3(20, 20, 20));
    skybox->SetTexture(textureNames);
    skybox->PrepareData();
    
    waterQuad=new WaterQuad();
    waterQuad->SetCamera(mainCamera);
    waterQuad->setPos(vec3(0,100,0));
    waterQuad->setScale(vec3(10000,10000,10000));
    waterQuad->SetEnv(skybox);
    waterQuad->SetWindow(window);
    waterQuad->AddRenderable(skybox);
    waterQuad->AddRenderable(cityModeller);
    waterQuad->Init();

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
    waterQuad->Render();
}


