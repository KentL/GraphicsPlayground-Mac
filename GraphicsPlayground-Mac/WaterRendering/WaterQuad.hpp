//
//  WaterQuad.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-04-30.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef WaterQuad_hpp
#define WaterQuad_hpp

#include <stdio.h>
#include "stdafx.h"
#include "Quad.hpp"
#include "W_BufferManager.h"
#include "W_VertexDeclaration.h"
#include "W_Material.h"
#include "W_MaterialManager.h"
#include "Camera.h"
#include "SkyBox.h"
#include "RenderTarget.h"
#include "Renderable.hpp"


class WaterQuad:public Geometry::Quad{
private:
    const string vShader = "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/water/water.vsh";
    const string fShader = "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/water/water.fsh";
    wolf::VertexBuffer* g_pVB = 0;
    wolf::VertexDeclaration* g_pDecl = 0;
    wolf::Program* program = 0;
    Camera* mainCamera = 0;
    Camera* reflectionCamera=0;
    RenderTarget* refractionTarget;
    RenderTarget* reflectionTarget;
    RenderTarget* screenTarget;
    SkyBox* skyBox;
    GLFWwindow* window;
    vec3 normal = vec3(0,1,0);
    vector<Renderable*> renderObjects;
    wolf::Texture* normalMap1;
    wolf::Texture* normalMap2;
    wolf::Texture* normalMap3;
    
    float speed=10;
    float round=0;
    int m_width,m_height;
    float waveHeight = 0;
    bool useNormal = false;
    
private:
    glm::mat3 CalculateWorldIT();
    glm::mat4 CalculateWVP();
    glm::mat4 CalculateWorld();
    glm::mat4 CalculateReflectionWVP();
    void RenderRefraction();
    void RenderReflection();
    
    
public:
    void Init();
    void Render();
    void SetCamera(Camera* camera);
    void SetEnv(SkyBox* skyBox);
    void SetWindow(GLFWwindow* window);
    void AddRenderable(Renderable* renderObject);
    void HandleKeyBoardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#endif /* WaterQuad_hpp */
