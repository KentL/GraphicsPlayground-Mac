//
// Created by Kent Li on 2017-09-24.
//

#ifndef GRAPHICSPLAYGROUND_MAC_CAUSTICEXAMPLE_H
#define GRAPHICSPLAYGROUND_MAC_CAUSTICEXAMPLE_H


#include <ExampleBase.hpp>
#include <common/TexturedPanel.h>
#include "CausticPanel.h"

class CausticExample: public ExampleBase {
private:
    CausticExample() {};
    TexturedPanel* ground = 0;
    CausticPanel* causticPanel = 0;
    Camera* mainCamera;
public:
    static CausticExample* getInstance()
    {
        static CausticExample* instance=new CausticExample;
        return instance;
    }
    GLFWwindow* window;
    void Render();
    void Initialize();
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
    void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos);

public:
    CausticExample(CausticExample const&) = delete;
    void operator=(CausticExample const&)  = delete;
};


#endif //GRAPHICSPLAYGROUND_MAC_CAUSTICEXAMPLE_H
