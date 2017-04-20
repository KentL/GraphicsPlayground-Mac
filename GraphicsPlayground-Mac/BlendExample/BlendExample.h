#pragma once//"
#include "ExampleBase.hpp"

class BlendExample:public ExampleBase
{
private:

    BlendExample() {}
    
public:
    static BlendExample* getInstance()
    {
        static BlendExample* instance = new BlendExample();
        return instance;
    }
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    
public:
    BlendExample(BlendExample const&) = delete;
    void operator=(BlendExample const&)  = delete;
};

