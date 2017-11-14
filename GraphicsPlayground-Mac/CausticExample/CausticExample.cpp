//
// Created by Kent Li on 2017-09-24.
//

#include "CausticExample.h"

void CausticExample::Initialize() {
    const string groundVSH = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/texturedPanel/TexturedPanel.vsh";
    const string groundPSH = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/texturedPanel/TexturedPanel.fsh";
    const string causticVSH = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/causticPanel/CausticPanel.vsh";
    const string causticPSH = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/shaders/causticPanel/CausticPanel.fsh";
    const string groundtex = "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/common/brick.dds";

    //******************set up camera *********************//
    mainCamera = new Camera();
    mainCamera->setPos(vec3(0,0,-15));
    mainCamera->setFOV(45);
    mainCamera->setNear(0.1f);
    mainCamera->setFar(1000.0f);
    mainCamera->setAspect(1280.0f / 720.0f);
    mainCamera->setWindow(window);

    ground = new TexturedPanel;
    ground->Initialize(groundVSH,groundPSH,groundtex);
    ground->scale(vec3(100,100,100));
    ground->SetCamera(mainCamera);

    causticPanel = new CausticPanel;
    causticPanel->Initialize(causticVSH,causticPSH);
    causticPanel->setPos(vec3(30,30,30));
    causticPanel->scale(vec3(100,100,100));
    causticPanel->SetCamera(mainCamera);
    causticPanel->SetNormalTextures(
            "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/water/normalmap.png",
    "/Users/kli/Documents/Graphics Programming/GraphicsPlayground-Mac/resource/picture/water/normalmap2.png");
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
}

void CausticExample::Render() {
    mainCamera->cameraMove();

    ground->Render();
    causticPanel->Render();
}

void CausticExample::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos) {
    mainCamera->HandleCursorPositionChange(window, newXPos, newYPos);
}
void CausticExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    mainCamera->HandleKeyInput(window, key, scancode, action, mods);
}
