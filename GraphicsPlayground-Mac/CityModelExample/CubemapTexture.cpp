#include "stdafx.h"
#include "CubemapTexture.h"

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

            string fileName = m_fileNames[i];

            int width, height;
            unsigned char* image =
            SOIL_load_image(fileName.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
            
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            SOIL_free_image_data(image);

		}
		catch (exception e)
		{
            std::cout << "Error loading texture" << m_fileNames[i] << std::endl;
		}

	}
	return true;
}

void CubemapTexture::Bind(GLenum TextureUnit)
{
	glActiveTexture(TextureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureObj);
}

