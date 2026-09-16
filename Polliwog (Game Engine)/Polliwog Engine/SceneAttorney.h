#pragma once

#ifndef _SceneAttorney
#define _SceneAttorney

#include "Scene.h"

class SceneAttorney
{
public:

    class GameLoop
    {
    private:
        friend class SceneManager;
        static void Update(Scene* p) { p->Update(); }

        static void Draw(Scene* p) { p->Draw(); }

        static Camera* getCamera(Scene* p) { return p->getCamera(); };
    };

public:
    class Xables
    {
        friend class Updatable;
        friend class Drawable;
        friend class Alarmable;
        friend class Inputable;
        friend class Collidable;
        friend class GameObject;

    private:
        static void Register(Updatable* a, UpdateManager::StorageListRef& deleteMe, Scene* p) { p->Register(a, deleteMe); }
        static void Deregister(const UpdateManager::StorageListRef& ref, Scene* p) { p->Deregister(ref); }

        static void Register(Drawable* a, DrawManager::StorageListRef& deleteMe, Scene* p) { p->Register(a, deleteMe); }
        static void Deregister(const DrawManager::StorageListRef& ref, Scene* p) { p->Deregister(ref); }

        static void Register(float t, Alarmable* a, AlarmManager::Alarm_ID id, AlarmManager::StorageListRef& deleteMe, Scene* p) { p->Register(t, a, id, deleteMe); }
        static void Deregister(Scene* p, AlarmManager::StorageListRef& ref) { p->Deregister(ref); }

        static void Register(Inputable* input, FROG_KEY k, EVENT_TYPE e, Scene* p) { p->Register(input, k, e); }
        static void Deregister(Inputable* input, FROG_KEY k, EVENT_TYPE e, Scene* p) { p->Deregister(input, k, e); }

        static void Register(Inputable* input, FROG_MOUSE k, EVENT_TYPE e, Scene* p) { p->Register(input, k, e); }
        static void Deregister(Inputable* input, FROG_MOUSE k, EVENT_TYPE e, Scene* p) { p->Deregister(input, k, e); }

        static void SubmitCommand(Scene* p, SceneCommand* cmd) { p->SubmitCommand(cmd); }

        static void SetOff(Scene* p, AlarmManager::Alarm_ID id) { p->SetOffAlarm(id); }

        static CollisionManager* getCollisionMgr(Scene* p) { return p->getCollisionMgr(); }
    };

};

#endif _SceneAgent