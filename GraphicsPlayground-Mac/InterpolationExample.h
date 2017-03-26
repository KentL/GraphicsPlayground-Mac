#pragma once
#include "ExampleBase.hpp"

class InterpolationExample:public ExampleBase
{
private:
    InterpolationExample() {}
    ;
    
public:
    static InterpolationExample* getInstance()
    {
        static InterpolationExample* instance=new InterpolationExample;
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    
public:
    InterpolationExample(InterpolationExample const&) = delete;
    void operator=(InterpolationExample const&)  = delete;
};

