#pragma once

#ifndef _AlarmManager
#define _AlarmManager

#include <map>

class Alarmable;

class AlarmManager
{
public:
	enum class Alarm_ID { Alarm_1 = 0, Alarm_2 = 1, Alarm_3 = 2, Alarm_4 = 3, Alarm_5 = 4};
	static const int AlarmNum = 5; //Maximum number of alarms

private:
	using AlarmEvent = std::pair< Alarmable*, Alarm_ID >; //A pair to be used inside the map

	// Data Structure: Hashmaps
	using TimeLineMap = std::multimap<float, AlarmEvent>; //Uses time as the key
	TimeLineMap timeline;

public:
	AlarmManager() = default;
	AlarmManager(const AlarmManager&) = delete;
	AlarmManager& operator=(const AlarmManager&) = delete;
	~AlarmManager() = default;

	using StorageListRef = TimeLineMap::iterator;

	//
	// Scene Registration
	//
	void Register(float t, Alarmable* drawing, AlarmManager::Alarm_ID id, StorageListRef& ref);
	void Deregister(const StorageListRef& ref);
	void ProcessAlarms();

	// Sets off any given alarm automatically and removes it from the map
	void setOff(AlarmManager::Alarm_ID id);
};


#endif _AlarmManager