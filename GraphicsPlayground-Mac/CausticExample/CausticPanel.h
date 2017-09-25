//
// Created by Kent Li on 2017-09-24.
//

#ifndef GRAPHICSPLAYGROUND_MAC_CAUSTICPANEL_H
#define GRAPHICSPLAYGROUND_MAC_CAUSTICPANEL_H

#include <Renderable.hpp>
#include <CityModelExample/Camera.h>
#include <CityModelExample/struct.h>
#include <W_MaterialManager.h>
class CausticPanel : public Renderable, public Node {
public:
    void Render();
    void Render(RenderTarget *target) override;
    void SetCamera(Camera *camera) override;
    void Initialize(string vsh, string psh, string textureFile);

private:
    Camera* mainCamera;
    wolf::VertexBuffer* g_pVB = 0;
    wolf::VertexDeclaration* g_pDecl = 0;

    wolf::MaterialManager* g_Mat_Manager = 0;
    wolf::Material* mat = 0;
    wolf::Texture* tex = 0;

    VertexWithUV vertices[6] = {
            // Top
            { -0.5f, 0.0f, 0.5f, 0.0f, 0.0f},
            { -0.5f, 0.0f, -0.5f, 0.0f, 1.0f},
            { 0.5f, 0.0f, -0.5f, 1.0f, 1.0f},
            { 0.5f, 0.0f, -0.5f, 1.0f, 1.0f},
            { 0.5f, 0.0f, 0.5f, 1.0f, 0.0f},
            { -0.5f, 0.0f, 0.5f, 0.0f, 0.0f}
    };
};


#endif //GRAPHICSPLAYGROUND_MAC_CAUSTICPANEL_H
