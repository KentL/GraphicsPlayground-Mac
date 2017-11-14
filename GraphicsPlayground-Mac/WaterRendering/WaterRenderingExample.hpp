//
//  WaterRenderingExample.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-04-29.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef WaterRenderingExample_hpp
#define WaterRenderingExample_hpp

#include "ExampleBase.hpp"
#include "SkyBox.h"
#include "WaterQuad.hpp"

class WaterRenderingExample:public ExampleBase
{
private:
    
    WaterRenderingExample() {}
    SkyBox* skybox;
    Camera* mainCamera;
    WaterQuad* waterQuad;
public:
    static WaterRenderingExample* getInstance()
    {
        static WaterRenderingExample* instance = new WaterRenderingExample();
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos);
    GLFWwindow* window;;
public:
    WaterRenderingExample(WaterRenderingExample const&) = delete;
    void operator=(WaterRenderingExample const&)  = delete;
};

#endif /* WaterRenderingExample_hpp */
