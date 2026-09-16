#pragma once

#ifndef _AssetAttorney
#define _AssetAttorney

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "TerrainManager.h"

class AssetAttorney
{
public:

    class Engine
    {
        friend class Tadpole;

    private:
        static void ModelTerminate() { ModelManager::Terminate(); }
        static void ShaderTerminate() { ShaderManager::Terminate(); }
        static void TextureTerminate() { TextureManager::Terminate(); }
        static void TerrainTerminate() { TerrainManager::Terminate(); };

        static void LoadModelResources() { ModelManager::LoadDefaultResources(); }
        static void LoadShaderResources() { ShaderManager::LoadDefaultResources(); }
        static void LoadTextureResources() { TextureManager::LoadDefaultResources(); }
    };
};

#endif _AssetAttorney