#pragma once
#include "ExampleBase.hpp"
class RotateCubeExample:public ExampleBase
{
   
private:
    RotateCubeExample() {}
    
public:
    static RotateCubeExample*  getInstance()
    {
        static RotateCubeExample* instance=new RotateCubeExample;
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);

    
public:
    RotateCubeExample(RotateCubeExample const&) = delete;
    void operator=(RotateCubeExample const&)  = delete;
};

