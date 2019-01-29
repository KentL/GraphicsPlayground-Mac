#include <DynamicEnvMappedSphere.hpp>

Geometry::DynamicEnvMappedSphere::~DynamicEnvMappedSphere() {
	this->sphereVertices->clear();
	delete this->sphereVertices;
}


Geometry::DynamicEnvMappedSphere::DynamicEnvMappedSphere(std::string name, float accurity) {
	this->accurity = accurity;
	this->name = name;
}

string Geometry::DynamicEnvMappedSphere::getVertexShader() { return vertexShader; }
string Geometry::DynamicEnvMappedSphere::getFragmentShader() { return fragmentShader; }

void Geometry::DynamicEnvMappedSphere::Render(RenderTarget *target) {
	target->Bind();
	this->Render();
}

void Geometry::DynamicEnvMappedSphere::SetCamera(Camera * camera)
{
	this->mainCamera = camera;
}

void Geometry::DynamicEnvMappedSphere::Initialize()
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

	envMapRenderTarget = new CubeMapRenderableTarget(100, 100);
}

void Geometry::DynamicEnvMappedSphere::Render()
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
	mat->Apply();

	glDrawArrays(GL_TRIANGLES, 0, sphereVertices->size());
}




