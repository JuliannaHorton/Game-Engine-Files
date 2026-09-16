#pragma once

#ifndef _ModelAttorney
#define _ModelAttorney

#include "Model.h"

class ModelAttorney
{
public:
    friend class GraphicObject_TextureLight;
    friend class GraphicObject_Texture;
    friend class GraphicObject_Color;
    friend class GraphicObject_Light;
    friend class GraphicObject_WireFrame;
    friend class TerrainModel;
    friend class SkyBox;
    friend class FlatPlane;
    friend class SpriteFlatPlane;

    friend class ShaderTextureLight;
    friend class PointLightManager;
    friend class SpotLightManager;

private:
    static void SetToContext(Model* m) { m->Model::SetToContext(); };
    static void RenderMesh(Model* m, int meshnum) { m->Model::RenderMesh(meshnum); };
};

#endif _ModelAttorney