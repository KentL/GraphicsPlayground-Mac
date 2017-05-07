#ifndef PARTICLEEXAMPLE
#define PARTICLEEXAMPLE
#include "stdafx.h"
#include "ExampleBase.hpp"
#include "W_VertexBuffer.h"
#include "W_VertexDeclaration.h"
#include "W_Program.h"
#include "Camera.h"
#include "Effect.h"
#include "SkyBox.h"

class ParticleSystemExample:public ExampleBase
{
    friend class Game;
private:
    ParticleSystemExample() {}

    Camera* mainCamera;
    GLFWwindow* window;
    SkyBox* skybox;
    
    Effect* smoke_fire_effect;
    Effect* rain_cloud_effect;
    Effect* current_effect;
    float timer;
    float last_time = 0;
    int counter = 0;
    
public:
    static ParticleSystemExample*  getInstance()
    {
        static ParticleSystemExample* instance=new ParticleSystemExample;
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos);
    
    
public:
    ParticleSystemExample(ParticleSystemExample const&) = delete;
    void operator=(ParticleSystemExample const&)  = delete;

};

#endif
