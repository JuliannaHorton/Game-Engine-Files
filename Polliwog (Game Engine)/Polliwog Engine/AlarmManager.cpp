#include "AlarmManager.h"
#include "AlarmAttorney.h"
#include "TimeManager.h"

/// <summary>
/// 
/// /brief A singleton class that stores and manages active Alarmables.
/// 
/// </summary>

void AlarmManager::Register(float t, Alarmable* alert, Alarm_ID id, StorageListRef& ref)
{
	AlarmEvent alarm = { alert, id };
	ref = timeline.insert({ t, alarm });

	AlarmAttorney::GameLoop::SetDelete(alert, ref, id);
}

void AlarmManager::Deregister(const StorageListRef& ref)
{
	timeline.erase(ref);
}

/// <summary>
/// 
/// ProcessAlarms iter
/// 
/// </summary>
void AlarmManager::ProcessAlarms()
{
	float time = TimeManager::GetTime();


	while (!timeline.empty() && timeline.begin()->first < time) //Loops through the list based on what alarm should be called first 
	{
		auto alert = timeline.begin();

		Alarmable* myAlarm = alert->second.first;
		Alarm_ID trigger = alert->second.second;
		AlarmAttorney::GameLoop::TriggerAlarm(myAlarm, trigger);

		timeline.erase(alert);
	}
}


void AlarmManager::setOff(AlarmManager::Alarm_ID id) //My added method
{
	for (auto alert = timeline.begin(); alert != timeline.end(); ++alert)
	{
		if (alert->second.second == id)
		{
			AlarmAttorney::GameLoop::TriggerAlarm(alert->second.first, id);
			timeline.erase(alert);
			break;
		}
	}
}
