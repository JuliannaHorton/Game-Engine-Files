#pragma once

#ifndef _DrawAttorney
#define _DrawAttorney

#include "Drawable.h"

class DrawAttorney
{
public:

    class GameLoop
    {
    private:
        friend class DrawManager;
        static void Draw(Drawable* p) { p->Draw(); }
        static void Draw2D(Drawable* p) { p->Draw2D(); }

        static void SetDelete(Drawable* p, const DrawManager::StorageListRef& ref) { p->setDelete(ref); };
    };

public:
    class Registration
    {
        friend class DrawRegistrationCmd;
        friend class DrawDeregistrationCmd;

    private:
        static void SceneRegistration(Drawable* p) { p->SceneRegistration(); }
        static void SceneDeregistration(Drawable* p) { p->SceneDeregistration(); }
    };

};

#endif _DrawAttorney