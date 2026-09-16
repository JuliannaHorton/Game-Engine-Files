#pragma once

#ifndef _GOAttorney
#define _GOAttorney

#include "GameObject.h"

class GOAttorney
{
public:

    class Registration
    {
        friend class GameObjectEntryCmd;
        friend class GameObjectExitCmd;

    private:
        static void ConnectToScene(GameObject* p) { p->ConnectToScene(); }
        static void DisconnectFromScene(GameObject* p) { p->DisconnectFromScene(); }
    };

};

#endif _GOAttorney