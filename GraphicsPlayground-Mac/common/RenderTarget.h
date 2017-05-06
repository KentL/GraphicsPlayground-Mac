//-----------------------------------------------------------------------------
// File:			RenderTarget.h
// Original Author:	Gordon Wood
//
// Simple little class to wrap FBO functionality for post-processing sample(s).
// This should *not* be considered a good implementation for a wrapper for FBOs,
// and this is why it's not included in wolf. It's used only to make the rest
// of the code here easier to follow
//-----------------------------------------------------------------------------
#ifndef RENDERTARGET_H_
#define RENDERTARGET_H_

#define GLFW_INCLUDE_GL3
#include "stdafx.h"
#include "W_Program.h"
#include "W_VertexBuffer.h"
#include "W_VertexDeclaration.h"

class RenderTarget
{
	public:
		//-------------------------------------------------------------------------
		// PUBLIC INTERFACE
		//-------------------------------------------------------------------------
		RenderTarget(unsigned int p_uiWidth, unsigned int p_uiHeight, bool p_bIsScreen = false);
		virtual ~RenderTarget();	

		void Bind() const;
		GLuint GetColorBuffer() const { return m_uiColorBuffer; }

        float GetWidth() const { return m_fWidth; }
        float GetHeight() const { return m_fHeight; }
    void ClearBuffer();
    
//		void Render(wolf::Program* p_pProgram, RenderTarget* p_pRenderTarget) const;
//		void Add(wolf::Program* p_pProgram, RenderTarget* p_pRenderTarget) const;
		//-------------------------------------------------------------------------

	private:
		//-------------------------------------------------------------------------
		// PRIVATE MEMBERS
		//-------------------------------------------------------------------------
		GLuint m_uiFBO;
		GLuint m_uiColorBuffer;
		GLuint m_uiDepthBuffer;

		//wolf::VertexBuffer*			m_pVB;
		//wolf::VertexDeclaration*	m_pDecl;
		float						m_fWidth;
		float						m_fHeight;
		glm::vec3					m_vPos;
		bool						m_bIsScreen;
		//-------------------------------------------------------------------------
};

#endif

