#pragma once

#ifndef _FontManAttorney
#define _FontManAttorney

#include "SpriteFontManager.h"

class FontManAttorney
{
public:

    class Engine
    {
    private:
        friend class Tadpole;

        static void Terminate() { SpriteFontManager::Terminate(); };
        static void LoadFontResources() { SpriteFontManager::LoadDefaultResources(); }
    };

};

#endif _FontManAttorney