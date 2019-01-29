#pragma once
#include <SingleColorSphere.h>
#include <CubeMapRenderableTarget.h>

namespace Geometry
{
	class DynamicEnvMappedSphere :public SingleColorSphere
	{
	private:
		std::string vertexShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/DynamicEnvMappedSphere.vsh";
		std::string fragmentShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/DynamicEnvMappedSphere.fsh";
	protected:
		std::string name;
		virtual string getVertexShader();
		virtual string getFragmentShader();
		CubeMapRenderableTarget* envMapRenderTarget;
	public:

		void Initialize();

		~DynamicEnvMappedSphere();
		DynamicEnvMappedSphere(std::string name, float accurity);

		// Inherited via Renderable
		virtual void Render(RenderTarget * target) override;

		virtual void SetCamera(Camera * camera) override;
		void Render();
		

	};
}

