#ifndef _Alarmable
#define _Alarmable

#include "AlarmManager.h"
#include "RegistrationState.h"

class AlarmRegistrationCmd;
class AlarmDeregistrationCmd;

class Alarmable
{
	friend class AlarmAttorney;
public:
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;
	virtual ~Alarmable();

	void SubmitAlarmRegistration(float t, AlarmManager::Alarm_ID id);
	void SubmitAlarmDeregistration(AlarmManager::Alarm_ID id);

	void SetOffAlarm(AlarmManager::Alarm_ID id);

private:
	AlarmManager::StorageListRef pMyDeleteRef; //Reference back to the alarm
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED; //Registration State

	//Commands to be processed by the Scene Command Pattern
	AlarmRegistrationCmd* pRegistrationCmd;
	AlarmDeregistrationCmd* pDeregistrationCmd;

	void AlarmRegistration(float t, AlarmManager::Alarm_ID id);
	void AlarmDeregistration(AlarmManager::Alarm_ID id);

	//Called in the Scene, loops through alarms
	void TriggerAlarm(AlarmManager::Alarm_ID id);

	//Sets the Delete reference
	void setDelete(const AlarmManager::StorageListRef& ref, AlarmManager::Alarm_ID id);


	//3 Alarms MAX
	virtual void Alarm1() {};
	virtual void Alarm2() {};
	virtual void Alarm3() {};
	virtual void Alarm4() {};
	virtual void Alarm5() {};


	//
	// Data stored with each kry
	//
	struct RegistrationData
	{
		AlarmManager::StorageListRef pMyDeleteRef;
		RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		AlarmRegistrationCmd* pRegistrationCmd;
		AlarmDeregistrationCmd* pDeregistrationCmd;
	};

	RegistrationData RegData[AlarmManager::AlarmNum];
};


#endif _Alarmable