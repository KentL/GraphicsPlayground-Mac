#pragma once
#include <RenderableSphere.h>
#include <Renderable.hpp>
#include <Node.h>
#include <W_MaterialManager.h>
#include <SingleColorSphere.h>

namespace Geometry
{
	class TexturedSphere :public SingleColorSphere
	{
	private:
		string textureFile;
		wolf::Texture* tex = 0;
	protected:
		void Initialize();

	public:
		// D:\workspace\kentli\graphics\GraphicsPlayground-Mac\*/
		string vertexShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/TexturedSphere.vsh" ;
		string fragmentShader = "D:/workspace/kentli/graphics/GraphicsPlayground-Mac/shaders/Geometry/TexturedSphere.fsh" ;

		~TexturedSphere();
		TexturedSphere(float accurity,string texture);

		// Inherited via Renderable
		virtual void Render(RenderTarget * target) override;

		virtual void SetCamera(Camera * camera) override;
		void Render();

	};
}

