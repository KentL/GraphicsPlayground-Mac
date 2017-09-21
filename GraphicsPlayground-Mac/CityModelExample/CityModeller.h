#ifndef CITYMODELLER
#define CITYMODELLER

#define SIZE            70
#define TIME_ELAPSE_SPEED 10

#include <vector>
#include "struct.h"
#include "AABBCollider.h"
#include "Camera.h"
#include "AABBCollider.h"
#include "W_Texture.h"
#include "W_TextureManager.h"
#include "W_MaterialManager.h"
#include "DirectionalLight.h"
#include "SurfaceMaterial.h"
#include "W_BufferManager.h"
#include "MouseInputHandler.hpp"
#include "KeyboardInputHandler.hpp"
#include "Renderable.hpp"

using namespace std;

class CityModeller:public KeyboardInputHandler, public Renderable
{
private:
	vector<building*>* buildingStore;
	vector<road*>*     roadStore;
	vector<Vertex2>*  city_vertices_data;
	vector<singlegrid*>* cross;
	vector<singlegrid*>* buildingBase;
	vector<singlegrid*>* space;
	vector<Colliders::AABBCollider*>* aabbCollidersCollection;
	bool key_l_pressed = false;//record how many times key "L" is pressed to turn light effect on and off
	bool rotate_light = true;//Flag to determine whether light rotates or not
	wolf::VertexBuffer* g_pVB1 = 0;
	wolf::VertexDeclaration* g_pDecl = 0;
	wolf::Material* mat = 0;
	wolf::Texture* tex_map = 0;
	SurfaceMaterial* g_maskSurface;
	DirectionalLight* g_light;
	Camera* mainCamera;
    GLFWwindow* window;
	float last_time_key_l_pressed;//The last time that key 'L' is pressed to turn light on and off
	float lightAngle;
	vec4 waterPanel;

public:	vector<Vertex1>* collider_vertex;//For debug
		

private:
	void loadBuffer();
	
public:
	CityModeller();
	~CityModeller();
	void generateCityLayoutData();
	std::vector<Vertex2>* getBuffer();
	std::vector<Colliders::AABBCollider*>* GetAABBColliders();
	void clearBuffer();
	void SetTexture(const string& tex);
	void SetProgram(const string& vsh, const string& fsh);
    void Render();
	void Render(RenderTarget* target);
	void SetCamera(Camera* mainCamera);
    void SetWindow(GLFWwindow* window);
	void SetClipPanel(vec4 clipPanel);
public:
	bool grids[SIZE][SIZE];
	int w, h, l; //width length height of a building
	int wMax, hMax, lMax;
	int row1, row2, column1, column2;
    float lastT = 0;
    void HandleKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};
#endif
