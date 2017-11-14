//
// Created by Kent Li on 2017-09-24.
//

#include "CausticPanel.h"

void CausticPanel::Render(RenderTarget *target) {
    target->Bind();
    this->Render();
}

void CausticPanel::SetCamera(Camera *camera) {
    this->mainCamera = camera;
}

void CausticPanel::SetNormalTextures(string textureFile1, string textureFile2) {
    wolf::TextureManager* textureManager = wolf::TextureManager::Inst();

    normalTex1 = textureManager->CreateTexture(textureFile1);
    normalTex1->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_Linear);
    normalTex1->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);

    normalTex2 = textureManager->CreateTexture(textureFile2);
    normalTex2->SetFilterMode(wolf::Texture::FM_Linear, wolf::Texture::FM_Linear);
    normalTex2->SetWrapMode(wolf::Texture::WM_Repeat, wolf::Texture::WM_Repeat);
    mat->SetTexture("normalTex1", normalTex1);
    mat->SetTexture("normalTex2", normalTex2);
}

void CausticPanel::Initialize(string vsh, string psh) {
    wolf::BufferManager* bufferManager = wolf::BufferManager::Inst();
    g_pVB = bufferManager->CreateVertexBuffer(vertices, sizeof(vertices));

    mat = g_Mat_Manager->CreateMaterial("caustic_panel_material");
    mat->SetProgram(vsh, psh);

    g_pDecl = new wolf::VertexDeclaration();
    g_pDecl->Begin();
    g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_Tangent, 3, wolf::CT_Float);
    g_pDecl->SetVertexBuffer(g_pVB);
    g_pDecl->End();
}

void CausticPanel::Render() {
    round ++;

    glm::mat4 mProj = mainCamera->getProjectionMatrix();
    glm::mat4 mView = mainCamera->getViewMatrix();
    glm::mat4 model = this->getTransform();

    // Bind Uniforms
    mat->SetUniform("projection", mProj);
    mat->SetUniform("view", mView);
    mat->SetUniform("model", model);
    mat->SetUniform("modelIT", this->GetModelIT());
    mat->SetUniform("time", round/5000.0);
    mat->SetUniform("PanelNormal", vec3(0,1,0));
    mat->SetUniform("PanelTangent", vec3(1,0,0));

    // Set up source data
    g_pDecl->Bind();
    mat->Apply();

    glDrawArrays(GL_TRIANGLES,0, sizeof(vertices) / sizeof(vertices[0]));
}

glm::mat3 CausticPanel::GetModelIT() {
    glm::mat4 model = this->getTransform();
    glm::mat3 modelIT(model);
    modelIT = glm::inverse(modelIT);
    modelIT = glm::transpose(modelIT);
    return modelIT;
}