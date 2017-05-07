#ifndef SKYBOX
#define SKYBOX

#include "struct.h"
#include "CubemapTexture.h"
#include "W_MaterialManager.h"
#include "Camera.h"
#include "RenderTarget.h"
#include "Renderable.hpp"

class SkyBox:public Renderable
{
private:
	CubemapTexture* m_cube_texture;
	Vertex1 m_vertices[36];
	vec3 m_position=vec3(0,0,0);
	vec3 m_scale=vec3(1.0f,1.0f,1.0f);
	wolf::VertexBuffer* g_pVB = 0;
	wolf::VertexDeclaration* g_pDecl = 0;
	wolf::Program* g_pProgram = 0;
	Camera* mainCamera;
    GLFWwindow* window;
    int m_width,m_height;
public:
	SkyBox();
	~SkyBox();
	void Render();
    void Render(RenderTarget* renderTarget);
	void SetPositon(vec3 pos);
	void SetScale(vec3 scale);
    void SetWindow(GLFWwindow* window);
	void SetCamera(Camera* mainCamera);
	void SetTexture(const string* filename);
	void SetProgram(const string& vsh, const string& fsh);
	void Init();


};

#endif // SKYBOX


