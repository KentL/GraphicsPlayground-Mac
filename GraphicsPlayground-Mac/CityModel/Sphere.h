#pragma once
#include "Node.h"
#include "struct.h"
#include "wolf\W_Material.h"
class Sphere :public Node
{
private:
	float radius;
	float accurity=1;
	bool first_time_render=true;
	vector<Vertex2>* vertex;
	wolf::VertexBuffer* vertex_buffer = 0;
	wolf::VertexDeclaration* declaration = 0;
	wolf::Material* mat;

	//-------Private method--------------//
	void loadBuffer();
public:
	Sphere();
	void setAccurity(float acc){ accurity = acc; };
	void setProgram(const string& vShader, const string& fShader);
	//void render();
	void setRadius(float r){ radius = r; };
	~Sphere();

};

