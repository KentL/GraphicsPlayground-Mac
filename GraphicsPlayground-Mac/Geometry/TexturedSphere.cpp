#include <TexturedSphere.hpp>



void Geometry::TexturedSphere::Initialize()
{
	this->sphereVertices = new vector<SphereVertex>();

	CreateSphere();

	wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
	vertexBuffer = bufferManager->CreateVertexBuffer(&sphereVertices->at(0), sizeof(SphereVertex)*sphereVertices->size());

	mat = matManager->CreateMaterial("Textured_Sphere_Material");
	mat->SetProgram(vertexShader, fragmentShader);

	vertexDec = new wolf::VertexDeclaration();
	vertexDec->Begin();
	vertexDec->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	vertexDec->SetVertexBuffer(vertexBuffer);
	vertexDec->End();

	wolf::TextureManager* textureManager = wolf::TextureManager::Inst();

	tex = textureManager->CreateTexture(this->textureFile);
	tex->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_Linear);
	tex->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

	mat->SetTexture("tex", tex);
}


Geometry::TexturedSphere::~TexturedSphere() {
	this->sphereVertices->clear();
	delete this->sphereVertices;
}
Geometry::TexturedSphere::TexturedSphere(float accurity,string tex)
{
	this->accurity = accurity;
	this->textureFile = tex;
	Initialize();
}

void Geometry::TexturedSphere::Render(RenderTarget *target) {
	target->Bind();
	this->Render();
}

void Geometry::TexturedSphere::Render()
{
	glm::mat4 mProj = mainCamera->getProjectionMatrix();
	glm::mat4 mView = mainCamera->getViewMatrix();
	glm::mat4 model = this->getTransform();

	// Bind Uniforms
	mat->SetUniform("projection", mProj);
	mat->SetUniform("view", mView);
	mat->SetUniform("model", model);

	// Set up source data
	vertexDec->Bind();
	mat->Apply();

	glDrawArrays(GL_TRIANGLES, 0, sphereVertices->size());
}
void Geometry::TexturedSphere::SetCamera(Camera * camera)
{
	this->mainCamera = camera;
}



