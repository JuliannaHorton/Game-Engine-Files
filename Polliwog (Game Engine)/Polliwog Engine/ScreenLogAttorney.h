#pragma once

#ifndef _ScreenLogAttorney
#define _ScreenLogAttorney

#include "ScreenLog.h"

class ScreenLogAttorney
{
public:

    class Engine
    {
    private:
        friend class Tadpole;

        static void Terminate() { ScreenLog::Terminate(); };
        static void Render() { ScreenLog::Render(); };
    };

};

#endif _ScreenLogAttorney