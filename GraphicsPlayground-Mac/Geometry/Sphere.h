#pragma once

#include "Node.h"
#include "struct.h"
#include "W_Material.h"
namespace Geometry
{
	class Sphere
	{
	private:
		float radius;
		float accurity = 1;
		vector<VertexWithUVNormal>* vertex;
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

}
