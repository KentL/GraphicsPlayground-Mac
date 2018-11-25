//
// Created by Kent Li on 2017-09-24.
//

#ifndef GRAPHICSPLAYGROUND_MAC_GEOMETRYEXAMPLE_H
#define GRAPHICSPLAYGROUND_MAC_GEOMETRYEXAMPLE_H


#include <ExampleBase.hpp>
#include <Camera.h>
#include <SingleColorSphere.h>
#include <TexturedSphere.hpp>
#include <EnvMappedSphere.hpp>
#include <EnvMappedTransparentSphere.hpp>
#include <SkyBox.h>

class GeometryExample : public ExampleBase {
private:
	GeometryExample() {};
	Camera* mainCamera;
	SingleColorSphere* singleColorSphere;
	TexturedSphere* texturedSphere;
	EnvMappedSphere* envMappedSphere;
	EnvMappedTransparentSphere* transparentSphere;
	SkyBox* skybox;

public:
	static GeometryExample* getInstance()
	{
		static GeometryExample* instance = new GeometryExample;
		return instance;
	}
	GLFWwindow* window;
	void Render();
	void Initialize();
	void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	void HandleCursorPositionChange(GLFWwindow* window, double newXPos, double newYPos);

public:
	GeometryExample(GeometryExample const&) = delete;
	void operator=(GeometryExample const&) = delete;
};


#endif //GRAPHICSPLAYGROUND_MAC_GEOMETRYEXAMPLE_H
