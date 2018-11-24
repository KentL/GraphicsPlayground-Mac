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
		string textureFile;
		CubemapTexture* envMap;

	protected:
		void Initialize();

	public:
		// D:\workspace\kentli\graphics\GraphicsPlayground-Mac\*/
		string vertexShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/EnvMappedSphere.vsh";
		string fragmentShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/EnvMappedSphere.fsh";

		~EnvMappedSphere();
		EnvMappedSphere(float accurity, const string* textures);

		// Inherited via Renderable
		virtual void Render(RenderTarget * target) override;

		virtual void SetCamera(Camera * camera) override;
		void Render();



	};
}

