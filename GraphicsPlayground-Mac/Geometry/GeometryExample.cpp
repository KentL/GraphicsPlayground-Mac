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

	texturedSphere = new TexturedSphere(0.01f, "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/resource/picture/Iron.png");
	texturedSphere->setLocation(vec3(10, 0, 0));
	texturedSphere->setRadius(5.0f);
	texturedSphere->SetCamera(mainCamera);

	//Initialize SkyBox properties
	string pictureDir = "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/resource/picture/citymodel/";
	string skyBoxTextures[] = { pictureDir + "skybox-png/skybox_texture_posX.png", pictureDir + "skybox-png/skybox_texture_negX.png",
		pictureDir + "skybox-png/skybox_texture_posY.png", pictureDir + "skybox-png/skybox_texture_negY.png",
		pictureDir + "skybox-png/skybox_texture_posZ.png", pictureDir + "skybox-png/skybox_texture_negZ.png" };
	string shaderDir = "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/";
	skybox = new SkyBox();
	skybox->SetCamera(mainCamera);
	skybox->SetWindow(window);
	skybox->SetPositon(vec3(0, 5, 0));
	skybox->SetProgram(shaderDir + "skybox.vsh", shaderDir + "skybox.fsh");
	skybox->SetScale(vec3(20, 20, 20));
	skybox->SetTexture(skyBoxTextures);
	skybox->Init();

	envMappedSphere = new EnvMappedSphere("reflectionSphere",0.01f, skyBoxTextures);
	envMappedSphere->Initialize();
	envMappedSphere->setLocation(vec3(20, 0, 0));
	envMappedSphere->setRadius(5.0f);
	envMappedSphere->SetCamera(mainCamera);

	transparentSphere = new EnvMappedTransparentSphere("transparentSphere",0.01f, skyBoxTextures);
	transparentSphere->Initialize();
	transparentSphere->setLocation(vec3(30, 0, 0));
	transparentSphere->setRadius(5.0f);
	transparentSphere->SetCamera(mainCamera);


}

void GeometryExample::Render() {
	skybox->Render();
	glEnable(GL_DEPTH_TEST);
	mainCamera->cameraMove();
	singleColorSphere->Render();
	texturedSphere->Render();
	envMappedSphere->Render();
	transparentSphere->Render();
}

void GeometryExample::HandleCursorPositionChange(GLFWwindow *window, double newXPos, double newYPos) {
	mainCamera->HandleCursorPositionChange(window, newXPos, newYPos);
}
void GeometryExample::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
	mainCamera->HandleKeyInput(window, key, scancode, action, mods);
}
