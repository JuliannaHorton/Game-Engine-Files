#pragma once

#ifndef _AlarmRegistrationCmd
#define _AlarmRegistrationCmd

#include "SceneCommand.h"
#include "AlarmManager.h"

class Alarmable;

class AlarmRegistrationCmd : public SceneCommand
{
public:

	AlarmRegistrationCmd() = default;
	AlarmRegistrationCmd(const AlarmRegistrationCmd&) = delete;
	AlarmRegistrationCmd& operator=(const AlarmRegistrationCmd&) = delete;
	~AlarmRegistrationCmd() = default; //This might be bad

	AlarmRegistrationCmd(Alarmable* Alert, AlarmManager::Alarm_ID id) : ptrAlert(Alert), ID(id) {};


	void setTime(float t);
	virtual void execute();

private:
	Alarmable* ptrAlert;
	AlarmManager::Alarm_ID ID;
	float time;
};


#endif _AlarmRegistrationCmd