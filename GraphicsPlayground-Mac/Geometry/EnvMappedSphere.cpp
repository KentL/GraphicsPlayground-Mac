#include <EnvMappedSphere.hpp>

string Geometry::EnvMappedSphere::getVertexShader() { return vertexShader; }
string Geometry::EnvMappedSphere::getFragmentShader() { return fragmentShader; }

void Geometry::EnvMappedSphere::Initialize()
{
	this->sphereVertices = new vector<SphereVertex>();

	CreateSphere();

	wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
	vertexBuffer = bufferManager->CreateVertexBuffer(&sphereVertices->at(0), sizeof(SphereVertex)*sphereVertices->size());

	mat = matManager->CreateMaterial(this->name);
	mat->SetProgram(getVertexShader(), getFragmentShader());

	vertexDec = new wolf::VertexDeclaration();
	vertexDec->Begin();
	vertexDec->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	vertexDec->SetVertexBuffer(vertexBuffer);
	vertexDec->End();

	envMap->Load();
}


Geometry::EnvMappedSphere::~EnvMappedSphere() {
	this->sphereVertices->clear();
	delete this->sphereVertices;
}
Geometry::EnvMappedSphere::EnvMappedSphere(string name,float accurity, const string* textures)
{
	this->accurity = accurity;
	this->name = name;
	envMap = new CubemapTexture(textures[0], textures[1], textures[2], textures[3], textures[4], textures[5]);
}

void Geometry::EnvMappedSphere::Render(RenderTarget *target) {
	target->Bind();
	this->Render();
}

void Geometry::EnvMappedSphere::Render()
{
	glm::mat4 mProj = mainCamera->getProjectionMatrix();
	glm::mat4 mView = mainCamera->getViewMatrix();
	glm::mat4 model = this->getTransform();

	// Bind Uniforms
	mat->SetUniform("projection", mProj);
	mat->SetUniform("view", mView);
	mat->SetUniform("model", model);
	mat->SetUniform("cameraPos", mainCamera->getPos());
	mat->SetUniform("envMap", 0);

	// Set up source data
	vertexDec->Bind();
	envMap->Bind(GL_TEXTURE0);
	mat->Apply();

	glDrawArrays(GL_TRIANGLES, 0, sphereVertices->size());
}
void Geometry::EnvMappedSphere::SetCamera(Camera * camera)
{
	this->mainCamera = camera;
}



