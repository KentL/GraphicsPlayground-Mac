#ifndef SKYBOX
#define SKYBOX

#include "struct.h"
#include "CubemapTexture.h"
#include "wolf\W_MaterialManager.h"
#include "Camera.h"

class SkyBox
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

public:
	SkyBox();
	~SkyBox();
	void Render();
	void SetPositon(vec3 pos);
	void SetScale(vec3 scale);
	void SetCamera(Camera* mainCamera);
	void SetTexture(const string* filename);
	void SetProgram(const string& vsh, const string& fsh);
	void PrepareData();


};

#endif // SKYBOX


