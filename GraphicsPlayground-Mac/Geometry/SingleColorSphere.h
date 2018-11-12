#pragma once
#include <RenderableSphere.h>
#include <Renderable.hpp>
#include <Node.h>
#include <W_MaterialManager.h>

namespace Geometry
{
	class SingleColorSphere :public RenderableSphere
	{
	protected:
		Camera * mainCamera;
		vec4 color;
		struct SphereVertex
		{
			GLfloat x, y, z;
		};
		void CreateSphere();
		void CreateHalfSphere(bool top);
		void Initialize();
		vector<SphereVertex>*  sphereVertices;

		//Wolf variables:
		wolf::VertexBuffer* vertexBuffer = 0;
		wolf::VertexDeclaration* vertexDec = 0;

		wolf::MaterialManager* matManager = 0;
		wolf::Material* mat = 0;

	public:
		// D:\workspace\kentli\graphics\GraphicsPlayground-Mac\*/
		string vertexShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/SingleColorSphere.vsh";
		string fragmentShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/SingleColorSphere.fsh";

		~SingleColorSphere();
		SingleColorSphere(float accurity, vec4 color);
		SingleColorSphere();

		// Inherited via Renderable
		virtual void Render(RenderTarget * target) override;

		virtual void SetCamera(Camera * camera) override;
		void Render();

	};
}

