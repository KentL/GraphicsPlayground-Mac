//
// Created by Kent Li on 2019-01-09.
//

#include "CubeMapRenderableTarget.h"

void CubeMapRenderableTarget::ClearBuffer(){
    for (int i = 0; i < 6; ++i) {
        Bind(i);
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }
}
CubeMapRenderableTarget::CubeMapRenderableTarget(unsigned int p_uiWidth, unsigned int p_uiHeight, bool p_bIsScreen)
        : m_uiFBO(0), m_uiColorBuffer(0), m_uiDepthBuffer(0), m_fWidth(p_uiWidth), m_fHeight(p_uiHeight)
{
    for (int i = 0; i < 6; ++i) {
        glGenFramebuffers(1,&m_uiFBO[i]);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO[i]);

        glGenTextures(1,&m_uiDepthBuffer[i]);
        glBindTexture(GL_TEXTURE_2D, m_uiDepthBuffer[i]);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, (unsigned int)p_uiWidth, (unsigned int)p_uiHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL );
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D, m_uiDepthBuffer[i], 0);

        glGenTextures(1,&m_uiColorBuffer[i]);
        glBindTexture(GL_TEXTURE_2D, m_uiColorBuffer[i]);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, (unsigned int)p_uiWidth, (unsigned int)p_uiHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL );
        glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, m_uiColorBuffer[i], 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

}

CubeMapRenderableTarget::~CubeMapRenderableTarget()
{
    for (int i = 0; i < 6; ++i) {
        glDeleteTextures(1, &m_uiColorBuffer[i]);
        glDeleteTextures(1, &m_uiDepthBuffer[i]);
        glDeleteFramebuffers(1, &m_uiFBO[i]);
    }
}

void CubeMapRenderableTarget::Bind(int frameBufferNumber) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO[frameBufferNumber]);
}