#pragma once

#ifndef _InputAttorney
#define _InputAttorney

#include "Inputable.h"

class InputAttorney
{
public:

    class PressandRelease
    {
    private:
        friend class SingleKeyManager;

        static void KeyPressed(Inputable* p, FROG_KEY k) { p->KeyPressed(k); }
        static void KeyReleased(Inputable* p, FROG_KEY k) { p->KeyReleased(k); }
    };

    class MousePressandRelease
    {
    private:
        friend class SingleMouseManager;

        static void KeyPressed(Inputable* p, FROG_MOUSE k) { p->KeyPressed(k); }
        static void KeyReleased(Inputable* p, FROG_MOUSE k) { p->KeyReleased(k); }
    };


    class Registration
    {
    private:
        friend class InputRegistrationCmd;
        friend class InputDeregistrationCmd;

        static void SceneRegistration(Inputable* p, FROG_KEY k, EVENT_TYPE e) { p->SceneRegistration(k, e); }
        static void SceneDeregistration(Inputable* p, FROG_KEY k, EVENT_TYPE e) { p->SceneDeregistration(k, e); }
    };

    class MouseRegistration
    {
    private:
        friend class MouseInputRegistrationCmd;
        friend class MouseInputDeregistrationCmd;

        static void SceneRegistration(Inputable* p, FROG_MOUSE k, EVENT_TYPE e) { p->SceneRegistration(k, e); }
        static void SceneDeregistration(Inputable* p, FROG_MOUSE k, EVENT_TYPE e) { p->SceneDeregistration(k, e); }
    };
};

#endif _InputAttorney