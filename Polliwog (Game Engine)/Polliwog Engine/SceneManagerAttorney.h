#pragma once

#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

class SceneManagerAttorney
{
public:
    class SceneChange
    {
    private:
        friend class SceneChangeAction;

        static void ChangeScene(Scene* p) { SceneManager::ChangeScene(p); }
    };

    class Engine
    {
    private:
        friend class Tadpole;

        static void Update() { SceneManager::Update(); }
        static void Draw() { SceneManager::Draw(); }
        static void Terminate() { SceneManager::Delete(); }
    };
};

#endif _SceneAttorney