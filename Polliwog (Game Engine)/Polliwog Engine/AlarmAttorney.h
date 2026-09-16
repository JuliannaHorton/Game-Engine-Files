#pragma once

#ifndef _AlarmAttorney
#define _AlarmAttorney

#include "Alarmable.h"

class AlarmAttorney
{
public:

    class GameLoop
    {
    private:
        friend class AlarmManager;
        static void TriggerAlarm(Alarmable* p, AlarmManager::Alarm_ID id) { p->TriggerAlarm(id); }

        static void SetDelete(Alarmable* p, const AlarmManager::StorageListRef& ref, AlarmManager::Alarm_ID id) { p->setDelete(ref, id); };
    };

public:
    class Registration
    {
        friend class AlarmRegistrationCmd;
        friend class AlarmDeregistrationCmd;

    private:
        static void AlarmRegistration(float t, Alarmable* p, AlarmManager::Alarm_ID id) { p->AlarmRegistration(t, id); }
        static void AlarmDeregistration(Alarmable* p, AlarmManager::Alarm_ID id) { p->AlarmDeregistration(id); }
    };

};

#endif _AlarmAttorney