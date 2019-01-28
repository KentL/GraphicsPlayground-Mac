#pragma once
#include <RenderableSphere.h>
#include <Renderable.hpp>
#include <EnvMappedSphere.hpp>


namespace Geometry
{
	class EnvMappedTransparentSphere :public EnvMappedSphere
	{
	protected :
		 string getVertexShader() override { return vertexShader; }
		 string getFragmentShader() override { return fragmentShader; }
	public:
		// D:\workspace\kentli\graphics\GraphicsPlayground-Mac\*/
		string vertexShader = "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/Geometry/EnvMappedTransparentSphere.vsh" ;
		string fragmentShader = "/home/kentli/Documents/workspace/kentli/GraphicsPlayground-Mac/shaders/Geometry/EnvMappedTransparentSphere.fsh" ;

		~EnvMappedTransparentSphere();
		EnvMappedTransparentSphere(string name, float accurity, const string* textures);
	};
}

