#ifndef CUBEMAPTEXTURE
#define CUBEMAPTEXTURE

#include "stdafx.h"

using namespace std;
using namespace glm;

class CubemapTexture
{
public:
	CubemapTexture(
		const string& PosXFileName, 
		const string& NegXFileName,
		const string& PosYFileName, 
		const string& NegYFileName, 
		const string& PosZFileName,
		const string& NegZFileName);
	~CubemapTexture();

	bool Load();

	void Bind(GLenum TextureUnit);

private:
	string m_fileNames[6];
	GLuint m_textureObj;
};

#endif