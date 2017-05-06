//
//  WaterRenderingExample.cpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-04-29.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#include "WaterRenderingExample.hpp"

void WaterRenderingExample::HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos) {
    
}

void WaterRenderingExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods){
}

void WaterRenderingExample::Initialize() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    string pictureDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/citymodel/";
    string shaderDir = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/";
    //Setup Camera
    mainCamera = new Camera();
    mainCamera->setPos(vec3(0, 0, 0));
    mainCamera->setFOV(45.0f);
    mainCamera->setNear(0.1f);
    mainCamera->setFar(1000.0f);
    mainCamera->setAspect(1280.0f / 720.0f);
    mainCamera->setWindow(window);
    
    //Initialize SkyBox properties
    string textureNames[] = { pictureDir+"skybox-png/skybox_texture_posX.png", pictureDir+"skybox-png/skybox_texture_negX.png",
								pictureDir+"skybox-png/skybox_texture_posY.png", pictureDir+"skybox-png/skybox_texture_negY.png",
								pictureDir+"skybox-png/skybox_texture_posZ.png", pictureDir+"skybox-png/skybox_texture_negZ.png" };
    
    skybox = new SkyBox();
    skybox->SetCamera(mainCamera);
    skybox->SetPositon(vec3(0, 5, 0));
    skybox->SetProgram(shaderDir+"skybox.vsh", shaderDir+"skybox.fsh");
    skybox->SetScale(vec3(20, 20, 20));
    skybox->SetTexture(textureNames);
    skybox->PrepareData();
    skybox->SetWindow(window);
    

    waterQuad=new WaterQuad();
    waterQuad->SetCamera(mainCamera);
    waterQuad->setPos(mainCamera->getPos());
    waterQuad->setScale(vec3(100,100,100));
    waterQuad->SetEnv(skybox);
    waterQuad->SetWindow(window);
    waterQuad->AddRenderable(skybox);
    waterQuad->Init();
}

void WaterRenderingExample::Render(){
    mainCamera->cameraMove();
    skybox->Render();
    waterQuad->Render();
}
