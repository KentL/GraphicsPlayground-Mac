#pragma once
#include <RenderableSphere.h>
#include <Renderable.hpp>
#include <Node.h>
#include <W_MaterialManager.h>
#include <SingleColorSphere.h>
#include <CubemapTexture.h>

namespace Geometry
{
	class EnvMappedSphere :public SingleColorSphere
	{
	private:
		string name;
		string textureFile;
		CubemapTexture* envMap;
		string vertexShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/EnvMappedSphere.vsh";
		string fragmentShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/EnvMappedSphere.fsh";
	protected:
		virtual string getVertexShader();
		virtual string getFragmentShader();
	public:
		
		void Initialize();

		~EnvMappedSphere();
		EnvMappedSphere(string name, float accurity, const string* textures);

		// Inherited via Renderable
		virtual void Render(RenderTarget * target) override;

		virtual void SetCamera(Camera * camera) override;
		void Render();



	};
}

