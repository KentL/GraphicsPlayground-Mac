//-----------------------------------------------------------------------------
// File:			RenderTarget.cpp
// Original Author:	Gordon Wood
//
// See header for notes
//-----------------------------------------------------------------------------
#include "RenderTarget.h" 
#include "W_BufferManager.h"

struct QuadVertex
{
	GLfloat x,y;
	GLfloat u,v;
};

static unsigned int nextPow2(unsigned int p_ui)
{
	p_ui--;
	p_ui |= p_ui >> 1;
	p_ui |= p_ui >> 2;
	p_ui |= p_ui >> 4;
	p_ui |= p_ui >> 8;
	p_ui |= p_ui >> 16;
	p_ui++;
	return p_ui;
}
void RenderTarget::ClearBuffer(){
    Bind();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
RenderTarget::RenderTarget(unsigned int p_uiWidth, unsigned int p_uiHeight, bool p_bIsScreen)
	: m_uiFBO(0), m_uiColorBuffer(0), m_uiDepthBuffer(0), m_fWidth(p_uiWidth), m_fHeight(p_uiHeight), m_bIsScreen(p_bIsScreen)
{
	float fPadW = (float) nextPow2(p_uiWidth);
	float fPadH = (float) nextPow2(p_uiHeight);

	if( !p_bIsScreen )
	{
		glGenFramebuffers(1,&m_uiFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO);

		glGenTextures(1,&m_uiDepthBuffer);
		glBindTexture(GL_TEXTURE_2D, m_uiDepthBuffer);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, (unsigned int)fPadW, (unsigned int)fPadH, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL );
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, m_uiDepthBuffer, 0);

		glGenTextures(1,&m_uiColorBuffer);
		glBindTexture(GL_TEXTURE_2D, m_uiColorBuffer);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, (unsigned int)p_uiWidth, (unsigned int)p_uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
		glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, m_uiColorBuffer, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

//	QuadVertex quadVertices[] = 
//	{
//		{ -1.0f, -1.0f, 0.0f, 0.0f },
//		{ 1.0f, -1.0f, 1.0f, 0.0f },
//		{ -1.0f, 1.0f, 0.0f, 1.0f },
//
//		{ -1.0f, 1.0f, 0.0f, 1.0f },
//		{ 1.0f, -1.0f, 1.0f, 0.0f },
//		{ 1.0f, 1.0f, 1.0f, 1.0f }
//	};
//
//	for( int i = 0; i < 6; i++ )
//	{
//		quadVertices[i].u *= m_fWidth / fPadW;
//		quadVertices[i].v *= m_fHeight / fPadH;
//	}
//
//    m_pVB = wolf::BufferManager::Inst()->CreateVertexBuffer(quadVertices, sizeof(QuadVertex) * 6);
//
//	m_pDecl = new wolf::VertexDeclaration();
//	m_pDecl->Begin();
//	m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
//	m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
//	m_pDecl->SetVertexBuffer(m_pVB);
//	m_pDecl->End();
}

RenderTarget::~RenderTarget()
{
	if( !m_bIsScreen )
	{
		glDeleteTextures(1, &m_uiColorBuffer);
		glDeleteTextures(1, &m_uiDepthBuffer);
		glDeleteFramebuffers(1, &m_uiFBO);
	}

//	wolf::BufferManager::Inst()->DestroyBuffer(m_pVB);
//	delete m_pDecl;
}

void RenderTarget::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO);
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glViewport( 0, 0, m_fWidth, m_fHeight );
}

//void RenderTarget::Render(wolf::Program* p_pProgram, RenderTarget* p_pRenderTarget) const
//{
//	Bind();
//
//	glBindTexture(GL_TEXTURE_2D, p_pRenderTarget->GetColorBuffer());
//
//	p_pProgram->Bind();
//	p_pProgram->SetUniform("tex",0);
//	m_pDecl->Bind();
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//}
//
//void RenderTarget::Add(wolf::Program* p_pProgram, RenderTarget* p_pRenderTarget) const
//{
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_ONE, GL_ONE);
//
//	glBindTexture(GL_TEXTURE_2D, p_pRenderTarget->GetColorBuffer());
//	glDrawArrays(GL_TRIANGLES, 0, 6);
//
//	glDisable(GL_BLEND);
//}
