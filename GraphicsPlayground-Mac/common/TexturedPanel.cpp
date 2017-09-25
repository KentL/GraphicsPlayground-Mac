//
// Created by Kent Li on 2017-09-24.
//

#include "TexturedPanel.h"

void TexturedPanel::Render(RenderTarget *target) {
    target->Bind();
    this->Render();
}

void TexturedPanel::SetCamera(Camera *camera) {
    this->mainCamera = camera;
}

void TexturedPanel::Initialize(string vsh, string psh, string textureFile) {
    wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
    wolf::TextureManager* textureManager = wolf::TextureManager::Inst();
    g_pVB = bufferManager->CreateVertexBuffer(vertices, sizeof(vertices));

    tex = textureManager->CreateTexture(textureFile);
    tex->SetFilterMode(wolf::Texture::FM_Nearest, wolf::Texture::FM_Nearest);
    tex->SetWrapMode(wolf::Texture::WM_Clamp, wolf::Texture::WM_Clamp);
    mat = g_Mat_Manager->CreateMaterial("texture_panel_material");
    mat->SetProgram(vsh, psh);
    mat->SetDepthTest(true);
    mat->SetBlend(false);
    mat->SetTexture("tex", tex);

    g_pDecl = new wolf::VertexDeclaration();
    g_pDecl->Begin();
    g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    g_pDecl->SetVertexBuffer(g_pVB);
    g_pDecl->End();
}

void TexturedPanel::Render() {
    glm::mat4 mProj = mainCamera->getProjectionMatrix();
    glm::mat4 mView = mainCamera->getViewMatrix();
    glm::mat4 model = this->getTransform();

    // Bind Uniforms
    mat->SetUniform("projection", mProj);
    mat->SetUniform("view", mView);
    mat->SetUniform("model", model);

    // Set up source data
    g_pDecl->Bind();
    mat->Apply();

    glDrawArrays(GL_TRIANGLES,0, sizeof(vertices) / sizeof(vertices[0]));
}
