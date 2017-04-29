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
class CityModelExample:public ExampleBase
{
    friend class Game;
private:
    CityModelExample() {}
    
    wolf::VertexBuffer* g_pVB1 = 0;
    wolf::VertexDeclaration* g_pDecl = 0;
    wolf::Program* g_pProgram1 = 0;
    
    wolf::MaterialManager* g_Mat_Manager = 0;
    wolf::Material* mat = 0;
    wolf::Texture* tex_map = 0;
    
    SurfaceMaterial* g_maskSurface;
    DirectionalLight* g_light;
    
    float angle = 0;
    
    Camera* mainCamera;
    CityModeller* cityModeller;
    SkyBox* skybox;
    
    float s_fRotation = 0;
    bool keypressed = false;

    
    GLFWwindow* window;
    
    
    int key_f_pressed_counter = 0;//record how many times key "F" is pressed to change the fov of maincamera
    int key_b_pressed_counter = 0;//record how many times key "B" is pressed to turn skybox-rendering on and off
    float last_time_key_f_pressed = 0;//Record the last time that key 'F' is pressed to change the fov of mainCamera
    float last_time_key_b_pressed = 0;//Record the last time that key 'B' is pressed to turn skybox-rendering on and off
    float last_render_time = 0;
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
