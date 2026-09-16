#pragma once

#ifndef _UpdateAttorney
#define _UpdateAttorney

#include "Updatable.h"

class UpdateAttorney
{
public:

    class GameLoop
    {
    private:
        friend class UpdateManager;
        static void Update(Updatable* p) { p->Update(); }

        static void SetDelete(Updatable* p, const UpdateManager::StorageListRef& ref) { p->setDelete(ref); };
    };

public:
    class Registration
    {
        friend class UpdateRegistrationCmd;
        friend class UpdateDeregistrationCmd;

    private:
        static void SceneRegistration(Updatable* p) { p->SceneRegistration(); }
        static void SceneDeregistration(Updatable* p) { p->SceneDeregistration(); }
    };

};

#endif _UpdateAttorney
