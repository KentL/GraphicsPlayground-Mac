#include "stdafx.h"
#include "CubemapTexture.h"
#include "glew\include\GL\glew.h"

using namespace glm;

CubemapTexture::CubemapTexture(
		const string& PosXFileName, 
		const string& NegXFileName,
		const string& PosYFileName, 
		const string& NegYFileName, 
		const string& PosZFileName,
		const string& NegZFileName)
{
	m_fileNames[0] = PosXFileName;
	m_fileNames[1] = NegXFileName;
	m_fileNames[2] = PosYFileName;
	m_fileNames[3] = NegYFileName;
	m_fileNames[4] = PosZFileName;
	m_fileNames[5] = NegZFileName;
}


CubemapTexture::~CubemapTexture()
{
}

bool CubemapTexture::Load()
{
	glGenTextures(1, &m_textureObj);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);

	
	for (int i = 0; i < 6; i++)
	{
		try
		{

			GLFWimage img;
			glfwReadImage(m_fileNames[i].c_str(), &img, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, img.Format, img.Width, img.Height, 0, img.Format, GL_UNSIGNED_BYTE, img.Data);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glfwFreeImage(&img);

		}
		catch (exception e)
		{
			cout << "Error loading texture" << m_fileNames[i] << endl;
		}

	}
	return true;
}

void CubemapTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}

