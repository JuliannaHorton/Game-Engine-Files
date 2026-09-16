#pragma once#pragma once

#ifndef _EngineAttorney
#define _EngineAttorney

#include "Model.h"
#include "Texture.h"
#include "ShaderBase.h"

class AssetAttorney
{
public:
    friend class Model;
    friend class Texture;
    friend class ShaderBase;

private:

    //static void GetContext() { Engine::GetContext(); }
    //static void GetDevice() { Engine::LoadDefaultResources(); }
};

#endif _AssetAttorney