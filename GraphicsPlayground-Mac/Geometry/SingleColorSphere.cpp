#include <SingleColorSphere.h>

void Geometry::SingleColorSphere::CreateHalfSphere(bool top) {
	int flag = top ? 1 : -1;

	const float acc = clamp(this->accurity, 0.01f, 1.0f);
	const float space = 90*acc;
	const float R = this->radius;

	for (float b = 0; b <= 90 - space; b += space)
	{
		//Assign our a loop to go through 360 degrees in intervals of our variable space
		for (float a = 0.0; a <= (360 - space); a += space) {

			float x, y, z;
			//point 1
			{
				x = R * sin((a) / 180 * PI) * sin((b) / 180 * PI);

				y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI) ;

				z = R * cos((b) / 180 * PI);

				this->sphereVertices->push_back(SphereVertex{ x, y, z*flag });
			}
			//point 2
			{
				x = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI);

				y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI);

				z = R * cos((b + space) / 180 * PI);

				this->sphereVertices->push_back(SphereVertex{ x, y, z*flag });

			}

			//point 3
			{
				x = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI);

				y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI);

				z = R * cos((b) / 180 * PI);

				this->sphereVertices->push_back(SphereVertex{ x, y, z*flag });

			}
			//point 4
			{

				x = R * sin((a + space) / 180 * PI) * sin((b) / 180 * PI);

				y = R * cos((a + space) / 180 * PI) * sin((b) / 180 * PI);

				z = R * cos((b) / 180 * PI);

				this->sphereVertices->push_back(SphereVertex{ x, y, z*flag });

			}

			//point 5
			{
				x = R * sin((a) / 180 * PI) * sin((b + space) / 180 * PI);

				y = R * cos((a) / 180 * PI) * sin((b + space) / 180 * PI);

				z = R * cos((b + space) / 180 * PI);

				this->sphereVertices->push_back(SphereVertex{ x, y, z*flag });

			}
			// point 6
			{
				x = R * sin((a + space) / 180 * PI) * sin((b + space) / 180 * PI);
				//The Y value here.
				y = R * cos((a + space) / 180 * PI) * sin((b + space) / 180 * PI);
				//	The Z value here.
				z = R * cos((b + space) / 180 * PI);

				this->sphereVertices->push_back(SphereVertex{ x, y, z*flag });
			}

		}
	}
}


void Geometry::SingleColorSphere::CreateSphere()
{
	

	this->sphereVertices->clear();

	CreateHalfSphere(true);
	CreateHalfSphere(false);
}

void Geometry::SingleColorSphere::Initialize()
{
	this->sphereVertices = new vector<SphereVertex>();

	CreateSphere();

	wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
	vertexBuffer = bufferManager->CreateVertexBuffer(&sphereVertices->at(0), sizeof(SphereVertex)*sphereVertices->size());

	mat = matManager->CreateMaterial("Single_Sphere_Material");
	mat->SetProgram(vertexShader, fragmentShader);

	vertexDec = new wolf::VertexDeclaration();
	vertexDec->Begin();
	vertexDec->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
	vertexDec->SetVertexBuffer(vertexBuffer);
	vertexDec->End();
}

Geometry::SingleColorSphere::SingleColorSphere( ){
	Initialize();
}

Geometry::SingleColorSphere::~SingleColorSphere(){
	this->sphereVertices->clear();
	delete this->sphereVertices;
}
Geometry::SingleColorSphere::SingleColorSphere(float accurity,vec4 color) { 
	this->color = color;
	this->accurity = accurity;

	Initialize(); 
}

void Geometry::SingleColorSphere::Render(RenderTarget *target) {
	target->Bind();
	this->Render();
}

void Geometry::SingleColorSphere::Render()
{
	glm::mat4 mProj = mainCamera->getProjectionMatrix();
	glm::mat4 mView = mainCamera->getViewMatrix();
	glm::mat4 model = this->getTransform();

	// Bind Uniforms
	mat->SetUniform("projection", mProj);
	mat->SetUniform("view", mView);
	mat->SetUniform("model", model);
	mat->SetUniform("color", this->color);

	// Set up source data
	vertexDec->Bind();
	mat->Apply();

	glDrawArrays(GL_TRIANGLES, 0, sphereVertices->size());
}
void Geometry::SingleColorSphere::SetCamera(Camera * camera)
{
	this->mainCamera = camera;
}



