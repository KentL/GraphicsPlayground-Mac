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
            //image format
            FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
            //pointer to the image, once loaded
            FIBITMAP *dib(0);
            //pointer to the image data
            BYTE* bits(0);
            //image width and height
            GLuint gl_texID;
            
            //check the file signature and deduce its format
            fif = FreeImage_GetFileType(fileName.c_str(), 0);
            if (fif == FIF_UNKNOWN)
                fif = FreeImage_GetFIFFromFilename(fileName.c_str());
            
            dib = FreeImage_Load(fif, fileName.c_str());
            //retrieve the image data
            bits = FreeImage_GetBits(dib);
            int m_uiWidth = FreeImage_GetWidth(dib);
            int m_uiHeight = FreeImage_GetHeight(dib);
            long format;
            switch (FreeImage_GetColorType(dib)) {
                case FIC_RGB: format = GL_RGB; break;
                case FIC_RGBALPHA: format = GL_RGBA; break;
                default: format = GL_RGB; break;
            }
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, m_uiWidth, m_uiHeight, 0, format, GL_UNSIGNED_BYTE, bits);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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

