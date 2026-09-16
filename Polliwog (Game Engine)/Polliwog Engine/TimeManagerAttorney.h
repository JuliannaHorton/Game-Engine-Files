#pragma once

#ifndef _TimeManagerAttorney
#define _TimeManagerAttorney

#include "TimeManager.h"

class TimeManagerAttorney
{
public:

    class Engine
    {
    public:
        friend class Tadpole;

    private:

        static void Terminate() { TimeManager::Delete(); }
        static void ProcessTime() { return TimeManager::ProcessTime(); }
    };

};

#endif _TimeManagerAttorney