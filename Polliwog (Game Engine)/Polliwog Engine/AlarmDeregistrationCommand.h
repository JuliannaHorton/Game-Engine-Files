#pragma once

#ifndef _AlarmDeregistrationCmd
#define _AlarmDeregistrationCmd

#include "SceneCommand.h"
#include "Alarmable.h"


class AlarmDeregistrationCmd : public SceneCommand
{
public:

	AlarmDeregistrationCmd() = default;
	AlarmDeregistrationCmd(const AlarmDeregistrationCmd&) = delete;
	AlarmDeregistrationCmd& operator=(const AlarmDeregistrationCmd&) = delete;
	~AlarmDeregistrationCmd() = default; //This might be bad

	AlarmDeregistrationCmd(Alarmable* Alert, AlarmManager::Alarm_ID id) : ptrAlert(Alert), ID(id) {};

	virtual void execute();

private:

	Alarmable* ptrAlert;
	AlarmManager::Alarm_ID ID;
};


#endif _AlarmDeregistrationCmd