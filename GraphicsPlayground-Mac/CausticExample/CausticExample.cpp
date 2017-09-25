//
// Created by Kent Li on 2017-09-24.
//

#include "CausticExample.h"

void CausticExample::Initialize() {
    const string vsh = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/texturedPanel/TexturedPanel.vsh";
    const string psh = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/texturedPanel/TexturedPanel.fsh";
    const string tex = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/common/brick.dds";

    //******************set up camera *********************//
    mainCamera = new Camera();
    mainCamera->setPos(vec3(0,0,-15));
    mainCamera->setFOV(45);
    mainCamera->setNear(0.1f);
    mainCamera->setFar(1000.0f);
    mainCamera->setAspect(1280.0f / 720.0f);
    mainCamera->setWindow(window);

    ground = new TexturedPanel;
    ground->Initialize(vsh,psh,tex);
    ground->scale(vec3(100,100,100));
    ground->SetCamera(mainCamera);
}

void CausticExample::Render() {
    mainCamera->cameraMove();
    ground->Render();
}

void CausticExample::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos) {
    mainCamera->HandleCursorPositionChange(window, newXPos, newYPos);
}
void CausticExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    mainCamera->HandleKeyInput(window, key, scancode, action, mods);
}
