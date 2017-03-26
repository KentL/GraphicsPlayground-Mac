#pragma once
#include "ExampleBase.hpp"
class RotateTextureCubeExample: public ExampleBase{
private:
    RotateTextureCubeExample() {}
    ;
    
public:
    static RotateTextureCubeExample* getInstance()
    {
        static RotateTextureCubeExample* instance=new RotateTextureCubeExample;
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);

    
public:
    RotateTextureCubeExample(RotateTextureCubeExample const&) = delete;
    void operator=(RotateTextureCubeExample const&)  = delete;
};

