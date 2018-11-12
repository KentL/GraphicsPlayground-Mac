//
// Created by Kent Li on 2017-09-24.
//

#include <GeometryExample.hpp>

void GeometryExample::Initialize() {

	//******************set up camera *********************//
	mainCamera = new Camera();
	mainCamera->setPos(vec3(0, 0, -15));
	mainCamera->setFOV(45);
	mainCamera->setNear(0.1f);
	mainCamera->setFar(1000.0f);
	mainCamera->setAspect(1280.0f / 720.0f);
	mainCamera->setWindow(window);

	singleColorSphere = new SingleColorSphere(0.01f,vec4{ 0.0f,0.0f,120.0f,1.0f });
	singleColorSphere->setLocation(vec3(0, 0, 0));
	singleColorSphere->setRadius(5.0f);
	singleColorSphere->SetCamera(mainCamera);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
}

void GeometryExample::Render() {
	mainCamera->cameraMove();
	singleColorSphere->Render();
}

void GeometryExample::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos) {
	mainCamera->HandleCursorPositionChange(window, newXPos, newYPos);
}
void GeometryExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
	mainCamera->HandleKeyInput(window, key, scancode, action, mods);
}
