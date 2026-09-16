#pragma once

#ifndef _TadpoleAttorney
#define _TadpoleAttorney

#include "Tadpole.h"

class TadpoleAttorney
{
public:

    class Time
    {
        friend class TimeManager;
        friend class FreezeTime;

    private:
        static float GetTime() { return Tadpole::GetTime(); }
    };

public:

    //class Main
    //{
    //    friend class WinMain;

    //private:
    //    static void FunRun() { Tadpole::funRun(); };

    //};
};

#endif _TadpoleAttorney