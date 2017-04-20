#include "stdafx.h"
#include "SkyBox.h"


SkyBox::SkyBox()
{

}


SkyBox::~SkyBox()
{
}

void SkyBox::PrepareData()
{/*	 4	__________5
      /|		 /|
l    / |	    / |	   /|\y+
e 0	/_________1/  |		|
f	| 7|_ _ _ _|_ /6	|
t	| /		   | /		|------->x+
  3 |/_________|/	   /
		front	2    |/_z+
									
				*/
	Vertex1 vertices[] = { { -1.0f, 1.0f, 1.0f },
						{ 1.0f, 1.0f, 1.0f },
						{ 1.0f, -1.0f, 1.0f },
						{ -1.0f, -1.0f, 1.0f },
						{ -1.0f, 1.0f, -1.0f },
						{ 1.0f, 1.0f, -1.0f },
						{ 1.0f, -1.0f, -1.0f },
						{ -1.0f, -1.0f, -1.0f },
						};
	Vertex1 m_vertices[] = { 
		//front
		vertices[0], vertices[1], vertices[2],
		vertices[0], vertices[3], vertices[2],
		//left
		vertices[0], vertices[3], vertices[7],
		vertices[0], vertices[4], vertices[7],
		//back
		vertices[4], vertices[7], vertices[6],
		vertices[5], vertices[4], vertices[6],
		//right
		vertices[5], vertices[2], vertices[6],
		vertices[5], vertices[1], vertices[2],
		//top
		vertices[0], vertices[1], vertices[5],
		vertices[0], vertices[4], vertices[5],
		//bottom
		vertices[2], vertices[6], vertices[7],
		vertices[2], vertices[3], vertices[7],
						};

	g_pVB = wolf::BufferManager::CreateVertexBuffer(m_vertices, sizeof(Vertex1) *36);
	g_pDecl = new wolf::VertexDeclaration();
	g_pDecl->Begin();
	g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	g_pDecl->SetVertexBuffer(g_pVB);
	g_pDecl->End();

	this->m_cube_texture->Load();
}

void SkyBox::SetCamera(Camera* mainCamera)
{
	this->mainCamera = mainCamera;
}

void SkyBox::SetTexture(const string* filenames)
{
	this->m_cube_texture = new CubemapTexture(filenames[0], filenames[1], filenames[2], filenames[3], filenames[4], filenames[5]);
}

void SkyBox::SetProgram(const string& vsh, const string& fsh)
{
	if (g_pProgram)
		wolf::ProgramManager::DestroyProgram(g_pProgram);

	this->g_pProgram =  wolf::ProgramManager::CreateProgram(vsh,fsh);
}

void SkyBox::SetPositon(vec3 pos)
{
	this->m_position = pos;
}

void SkyBox::SetScale(vec3 scale)
{
	this->m_scale = scale;
}

void SkyBox::Render()
{
	//glDepthFunc(GL_LEQUAL);

	vec3 cameraPos = mainCamera->getPos();
	mat4 scaleMatrix = glm::scale(m_scale.x, m_scale.y, m_scale.z);
	mat4 transMatrix = glm::translate(m_position.x + cameraPos.x, m_position.y + cameraPos.y, m_position.z + cameraPos.z);
	mat4 mWorld = transMatrix*scaleMatrix;
	mat4 mView = mainCamera->getViewMatrix();
	mat4 mProj= mainCamera->getProjectionMatrix();
	mat4 mWorldViewProj = mProj*mView*mWorld;

	g_pProgram->Bind();

	g_pProgram->SetUniform("WorldViewProj", mWorldViewProj);
	g_pProgram->SetUniform("sky_tex", 0);

	this->m_cube_texture->Bind(GL_TEXTURE0);
	g_pDecl->Bind();

	glDrawArrays(GL_TRIANGLES, 0, 36);
}