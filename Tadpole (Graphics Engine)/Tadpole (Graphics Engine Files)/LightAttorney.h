#pragma once

#ifndef _LightAttorney
#define _LightAttorney

#include "DirLightManager.h"
#include "PointLightManager.h"
#include "SpotLightManager.h"

class LightAttorney
{
public:
    friend class Engine;

private:
    static void UpdateSpotLight() { SpotLightManager::Update(); };
    static void UpdatePointLight() { PointLightManager::Update(); };

    static void DrawSpotLight() { SpotLightManager::Draw(); };
    static void DrawPointLight() { PointLightManager::Draw(); };

    static void SpotTerminate() { SpotLightManager::Terminate(); };
    static void PointTerminate() { PointLightManager::Terminate(); };
    static void DirTerminate() { DirLightManager::Terminate(); };

    static void SpotLoad() { SpotLightManager::LoadLights(); };
    static void PointLoad() { PointLightManager::LoadLights(); };
};

#endif _LightAttorney