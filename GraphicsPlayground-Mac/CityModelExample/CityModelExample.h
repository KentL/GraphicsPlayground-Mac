#ifndef CITYMODELEXAMPLE
#define CITYMODELEXAMPLE
#include "stdafx.h"
#include "ExampleBase.hpp"
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
#include "SurfaceMaterial.h"
#include "SkyBox.h"
#include "WaterQuad.hpp"

class CityModelExample:public ExampleBase
{
    friend class Game;
private:
    CityModelExample() {}
    

    Camera* mainCamera;
    CityModeller* cityModeller;
    SkyBox* skybox;
    WaterQuad* waterQuad;


    
    GLFWwindow* window;
    
    
    int key_f_pressed_counter = 0;//record how many times key "F" is pressed to change the fov of maincamera
    int key_b_pressed_counter = 0;//record how many times key "B" is pressed to turn skybox-rendering on and off
    float last_time_key_f_pressed = 0;//Record the last time that key 'F' is pressed to change the fov of mainCamera
    float last_time_key_b_pressed = 0;//Record the last time that key 'B' is pressed to turn skybox-rendering on and off
    void RebuildCityModel();
public:
    static CityModelExample*  getInstance()
    {
        static CityModelExample* instance=new CityModelExample;
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos);
    
    
public:
    CityModelExample(CityModelExample const&) = delete;
    void operator=(CityModelExample const&)  = delete;

};

#endif
