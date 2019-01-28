//
// Created by Kent Li on 2019-01-09.
//

#ifndef GRAPHICSPLAYGROUND_MAC_CUBEMAPRENDERABLETARGET_H
#define GRAPHICSPLAYGROUND_MAC_CUBEMAPRENDERABLETARGET_H


#include <stdafx.h>

class CubeMapRenderableTarget {
public:
    //-------------------------------------------------------------------------
    // PUBLIC INTERFACE
    //-------------------------------------------------------------------------
    CubeMapRenderableTarget(unsigned int p_uiWidth, unsigned int p_uiHeight, bool p_bIsScreen = false);
    virtual ~CubeMapRenderableTarget();

    void Bind(int frameBufferNum) const;
    GLuint GetColorBuffer(int frameBufferNum) const { return m_uiColorBuffer[frameBufferNum]; }

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
    GLuint* m_uiFBO;
    GLuint* m_uiColorBuffer;
    GLuint* m_uiDepthBuffer;

    float						m_fWidth;
    float						m_fHeight;
    //-------------------------------------------------------------------------
};


#endif //GRAPHICSPLAYGROUND_MAC_CUBEMAPRENDERABLETARGET_H
