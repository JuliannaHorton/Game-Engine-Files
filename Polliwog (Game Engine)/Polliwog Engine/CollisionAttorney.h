#pragma once

#ifndef _CollisionAttorney
#define _CollisionAttorney

#include "Collidable.h"

class CollisionAttorney
{
public:
    class Registration
    {
        friend class CollisionRegistrationCmd;
        friend class CollisionDeregistrationCmd;

    private:
        static void CollideRegistration(Collidable* p) { p->SceneRegistration(); }
        static void CollideDeregistration(Collidable* p) { p->SceneDeregistration(); }
    };

};

#endif _CollisionAttorney