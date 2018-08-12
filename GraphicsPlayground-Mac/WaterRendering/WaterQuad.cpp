//
//  WaterQuad.cpp
//  GraphicsPlayground-Mac
//
//  Created by Kent Li on 2017-04-30.
//  Copyright © 2017 Kent Li. All rights reserved.
//

#include "WaterQuad.hpp"
struct Vertex
{
    GLfloat x,y,z;
    GLfloat u, v;
    GLfloat nx, ny, nz;
    GLfloat tx, ty, tz;
};

void WaterQuad::Init(){
    Vertex m_vertices[] = {
        {VertexArray[0].x,VertexArray[0].y,VertexArray[0].z,0,1, 0, 1, 0, 1, 0, 0 },
        {VertexArray[1].x,VertexArray[1].y,VertexArray[1].z,1,1,0, 1, 0, 1, 0, 0 },
        {VertexArray[2].x,VertexArray[2].y,VertexArray[2].z,1,0, 0, 1, 0, 1, 0, 0 },
        {VertexArray[0].x,VertexArray[0].y,VertexArray[0].z,0,1, 0, 1, 0, 1, 0, 0 },
        {VertexArray[3].x,VertexArray[3].y,VertexArray[3].z,0,0,  0, 1, 0, 1, 0, 0 },
        {VertexArray[2].x,VertexArray[2].y,VertexArray[2].z,1,0, 0, 1, 0, 1, 0, 0 }
    };
    program=wolf::ProgramManager::Inst()->CreateProgram(vShader, fShader);
    
    normalMap1=wolf::TextureManager::Inst()->CreateTexture("D:/workspace/kentli/graphics/GraphicsPlayground-Mac/resource/picture/water/normalmap.png");
    normalMap3=wolf::TextureManager::Inst()->CreateTexture("D:/workspace/kentli/graphics/GraphicsPlayground-Mac/resource/picture/water/normalmap3.png");
    normalMap2=wolf::TextureManager::Inst()->CreateTexture("D:/workspace/kentli/graphics/GraphicsPlayground-Mac/resource/picture/water/normalmap2.png");


    
    g_pVB = wolf::BufferManager::Inst()->CreateVertexBuffer(m_vertices, sizeof(Vertex) *6);
    g_pDecl = new wolf::VertexDeclaration();
    g_pDecl->Begin();
    g_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_Normal, 3, wolf::CT_Float);
    g_pDecl->AppendAttribute(wolf::AT_Tangent, 3, wolf::CT_Float);
    g_pDecl->SetVertexBuffer(g_pVB);
    g_pDecl->End();
    
    reflectionCamera = new Camera();
    reflectionCamera->setFOV(45.0f);
    reflectionCamera->setNear(0.1f);
    reflectionCamera->setFar(1000.0f);
    reflectionCamera->setAspect(m_width / m_height);
    reflectionCamera->setWindow(window);
    
    
    refractionTarget=new RenderTarget(m_width,m_height);
    reflectionTarget=new RenderTarget(m_width,m_height);
    screenTarget=new RenderTarget(m_width,m_height,true);
}

void WaterQuad::Render(){
    RenderReflection();
    RenderRefraction();

    program->Bind();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, refractionTarget->GetColorBuffer());
    program->SetUniform("RefractionTex",0);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, reflectionTarget->GetColorBuffer());
    program->SetUniform("ReflectionTex",1);
    
    glActiveTexture(GL_TEXTURE2);
    normalMap1->Bind();
    normalMap1->SetWrapMode(wolf::Texture::WM_Repeat,wolf::Texture::WM_Repeat);
    normalMap1->SetFilterMode(wolf::Texture::FM_Linear,wolf::Texture::FM_Linear);
    program->SetUniform("NormalMap", 2);
    
    glActiveTexture(GL_TEXTURE3);
    normalMap2->Bind();
    normalMap2->SetWrapMode(wolf::Texture::WM_Repeat,wolf::Texture::WM_Repeat);
    normalMap2->SetFilterMode(wolf::Texture::FM_Linear,wolf::Texture::FM_Linear);
    program->SetUniform("NormalMap2", 3);
    
    glActiveTexture(GL_TEXTURE4);
    normalMap3->Bind();
    normalMap3->SetWrapMode(wolf::Texture::WM_Repeat,wolf::Texture::WM_Repeat);
    normalMap3->SetFilterMode(wolf::Texture::FM_Linear,wolf::Texture::FM_Linear);
    program->SetUniform("NormalMap3", 4);
    
    
    program->SetUniform("WorldViewProj", CalculateWVP());
    program->SetUniform("World", CalculateWorld());
    program->SetUniform("WorldIT", CalculateWorldIT());
    program->SetUniform("ReflectionWorldViewProj", CalculateReflectionWVP());
    program->SetUniform("LightDir", vec3(-1,-1,-1));
    program->SetUniform("MatSpecular",  vec4(.1,.1,.1,.1));
    program->SetUniform("LightSpecular", vec4(.1,.1,.1,.1));
    program->SetUniform("MatDiffuse",  vec4(0.6,0.6,0.6,0.6));
    program->SetUniform("LightDiffuse",  vec4(1,1,1,1));
    program->SetUniform("ViewDir", mainCamera->getViewDirection());
    program->SetUniform("CameraPos", mainCamera->getPos());
    program->SetUniform("WaveHeight1", waveHeight/4);
    program->SetUniform("WaveHeight2", waveHeight/2);
    program->SetUniform("WaveHeight3", waveHeight);
    program->SetUniform("UseNormal", useNormal);
    program->SetUniform("Time", speed*round/5000);
    program->SetUniform("QuadWidth", myScale.x);
    program->SetUniform("QuadHeight", myScale.y);

    program->SetUniform("UnderWater", mainCamera->getPos().y < this->getPos().y);
    round++;
    g_pDecl->Bind();
    screenTarget->Bind();

    glViewport(0, 0, m_width, m_height);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
void WaterQuad::HandleKeyBoardInput(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(action==GLFW_PRESS){
        switch (key) {
            case GLFW_KEY_H:
                waveHeight+=0.1;
                if (waveHeight>2) {
                    waveHeight=2;
                }
                break;
            case GLFW_KEY_G:
                waveHeight-=0.1;
                if (waveHeight<-1) {
                    waveHeight=-1;
                }
                break;
            case GLFW_KEY_N:
                useNormal = !useNormal;
                break;
            default:
                break;
        }

    }
}
void WaterQuad::SetCamera(Camera *camera){
    this->mainCamera=camera;
}
void WaterQuad::AddRenderable(Renderable *renderObject){
    renderObjects.push_back(renderObject);
}
void WaterQuad::RenderReflection(){
    
    double waterLevel = this->getPos().y;
    vec3 virtualCameraPosition = vec3(mainCamera->getPos().x,2* waterLevel - mainCamera->getPos().y,mainCamera->getPos().z);
    reflectionCamera->setPos(virtualCameraPosition);
    
    vec3 mainCameraViewDirection = mainCamera->getViewDirection();
    vec3 reflectionViewDirection = mainCameraViewDirection;
    reflectionViewDirection.y=mainCameraViewDirection.y*-1;
    reflectionViewDirection=glm::normalize(reflectionViewDirection);
    reflectionCamera->setViewDirection(reflectionViewDirection);


    reflectionTarget->ClearBuffer();

    glEnable(GL_CLIP_DISTANCE0);
    vec4 clipPanel;
    //If reflection camera is above water, that means actual camera is under water, we need to flip the panel
    if(reflectionCamera->getPos().y > waterLevel){
        clipPanel  =  vec4(0,-1,0,waterLevel);
    }else{
        clipPanel =  vec4(0,1,0,-waterLevel);
    }
    for (int i =0; i<renderObjects.size(); i++) {
        renderObjects.at(i)->SetCamera(reflectionCamera);
        renderObjects.at(i)->SetClipPanel(clipPanel);
        renderObjects.at(i)->Render(reflectionTarget);
        renderObjects.at(i)->SetCamera(mainCamera);
    }
    glDisable(GL_CLIP_DISTANCE0);


}
void WaterQuad::RenderRefraction(){
    double waterLevel = this->getPos().y;
    refractionTarget->ClearBuffer();
    glEnable(GL_CLIP_DISTANCE0);
    vec4 clipPanel;
    if(mainCamera->getPos().y < waterLevel){
        clipPanel  =  vec4(0,1,0,-waterLevel);
    } else{
        clipPanel = vec4(0,-1,0,waterLevel);
    }
    for (int i =0; i<renderObjects.size(); i++)
    {
        renderObjects.at(i)->SetCamera(mainCamera);
        renderObjects.at(i)->SetClipPanel(clipPanel);
        renderObjects.at(i)->Render(refractionTarget);
    }
    glDisable(GL_CLIP_DISTANCE0);

}
void WaterQuad::SetEnv(SkyBox *skyBox){
    this->skyBox=skyBox;
}
void WaterQuad::SetWindow(GLFWwindow *window){
    this->window=window;
    glfwGetFramebufferSize(window, &m_width, &m_height);
}
glm::mat4 WaterQuad::CalculateReflectionWVP(){
    mat4 scaleMatrix = glm::scale(myScale);
    mat4 transMatrix = glm::translate(vec3(myPosition.x, myPosition.y, myPosition.z));
    mat4 mWorld = transMatrix*scaleMatrix;
    mat4 mView = reflectionCamera->getViewMatrix();
    mat4 mProj= reflectionCamera->getProjectionMatrix();
    mat4 mWorldViewProj = mProj*mView*mWorld;
    return mWorldViewProj;
}
glm::mat4 WaterQuad::CalculateWVP()
{
    mat4 mWorld = this->CalculateWorld();
    mat4 mView = mainCamera->getViewMatrix();
    mat4 mProj= mainCamera->getProjectionMatrix();
    mat4 mWorldViewProj = mProj*mView*mWorld;
    return mWorldViewProj;
}

glm::mat4 WaterQuad::CalculateWorld(){
    mat4 scaleMatrix = glm::scale(myScale);
    mat4 transMatrix = glm::translate(vec3(myPosition.x, myPosition.y, myPosition.z));
    return transMatrix*scaleMatrix;
}

glm::mat3 WaterQuad::CalculateWorldIT(){
    glm::mat4 mWorld = CalculateWorld();
    glm::mat3 mWorldIT(mWorld);
    mWorldIT = glm::inverse(mWorldIT);
    mWorldIT = glm::transpose(mWorldIT);
    return mWorldIT;
}
