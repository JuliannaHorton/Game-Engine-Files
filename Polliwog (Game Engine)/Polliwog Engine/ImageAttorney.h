#pragma once

#ifndef _ImageAttorney
#define _ImageAttorney

#include "ImageManager.h"

class ImageAttorney
{
public:

    class Engine
    {
    private:
        friend class Tadpole;

        static void Terminate() { ImageManager::Terminate(); };
    };

};

#endif _ImageAttorney