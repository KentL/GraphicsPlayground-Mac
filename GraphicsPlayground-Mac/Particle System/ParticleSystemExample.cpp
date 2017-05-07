//========================================================================
// Week 5 - Buffers and Attributes
//
// Example 4: Rendering a cube, using our beginnings of Wolf
//========================================================================
#include "ParticleSystemExample.h"

void ParticleSystemExample::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos){
    mainCamera->HandleCursorPositionChange(window, newXPos, newYPos);
}
void ParticleSystemExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){
    mainCamera->HandleKeyInput(window, key, scancode, action, mods);
}
void ParticleSystemExample::Initialize()
{
    const string shaderDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/";
    const string pictureDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/citymodel/";
    //Initialize SkyBox properties
    const string skyboxTextures[] = { pictureDir+"skybox-png/skybox_texture_posX.png", pictureDir+"skybox-png/skybox_texture_negX.png",
								pictureDir+"skybox-png/skybox_texture_posY.png", pictureDir+"skybox-png/skybox_texture_negY.png",
								pictureDir+"skybox-png/skybox_texture_posZ.png", pictureDir+"skybox-png/skybox_texture_negZ.png" };
    
    
    smoke_fire_effect = new Effect("/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/XMLs/SmokeFireEffect/smoke&fire_effect.xml");
    rain_cloud_effect = new Effect("/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/XMLs/RainCloudEffect/rain&cloud_effect.xml");
    
    //******************set up camera *********************//
    mainCamera = new Camera();
    mainCamera->setPos(vec3(0,0,-15));
    mainCamera->setFOV(45);
    mainCamera->setNear(0.1f);
    mainCamera->setFar(1000.0f);
    mainCamera->setAspect(1280.0f / 720.0f);
    mainCamera->setWindow(window);
    
    smoke_fire_effect->setCamera(mainCamera);
    rain_cloud_effect->setCamera(mainCamera);
    
    skybox = new SkyBox();
    skybox->SetCamera(mainCamera);
    skybox->SetWindow(window);
    skybox->SetPositon(vec3(0, 5, 0));
    skybox->SetProgram(shaderDir+"skybox.vsh", shaderDir+"skybox.fsh");
    skybox->SetScale(vec3(20, 20, 20));
    skybox->SetTexture(skyboxTextures);
    skybox->Init();
    
    current_effect = rain_cloud_effect;
    current_effect->start();
}

void ParticleSystemExample::Render()
{
    mainCamera->cameraMove();
    skybox->Render();
    if (glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS && (timer - last_time)>0.5)
    {
        last_time = glfwGetTime();
        counter++;
        if ((counter-1) % 2 == 0)
        {
            current_effect = smoke_fire_effect;
        }
        else
        {
            current_effect = rain_cloud_effect;
        }
        current_effect->start();
        
    }
    glEnable(GL_DEPTH_TEST);
    current_effect->update(glfwGetTime() - timer);
    current_effect->render();
    timer = glfwGetTime();

}


