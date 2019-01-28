//
//  Game.hpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-03-26.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "InterpolationExample.h"
#include "RotateCubeExample.h"
#include "RotateTextureCubeExample.h"
#include "BlendExample.h"
#include "CityModelExample.h"
#include "WaterRenderingExample.hpp"
#include "ParticleSystemExample.h"
#include <CausticExample/CausticExample.h>
#include <GeometryExample.hpp>

class Game
{
    
private:
    Game() {}
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static ExampleBase* example;
    GLFWwindow* window ;

public:
    static Game*  Inst()
    {
        static Game* instance=new Game;
        return instance;
    }
    void Init(int argc, char *argv[]);
    void Run();
    
public:
    Game(Game const&) = delete;
    void operator=(Game const&)  = delete;
};


#endif /* Game_hpp */
