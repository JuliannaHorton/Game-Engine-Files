#include "Alarmable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include "TimeManager.h"

/// <summary>
/// /brief Class type for handling alarm processing and activation for in-game events
/// </summary>

//
// All needed registers stored, so that its not calling new with every command
//
Alarmable::Alarmable()
{
	RegData[0].pDeregistrationCmd = pDeregistrationCmd = new AlarmDeregistrationCmd(this, AlarmManager::Alarm_ID::Alarm_1);
	RegData[0].pRegistrationCmd = pRegistrationCmd = new AlarmRegistrationCmd(this, AlarmManager::Alarm_ID::Alarm_1);

	RegData[1].pDeregistrationCmd = pDeregistrationCmd = new AlarmDeregistrationCmd(this, AlarmManager::Alarm_ID::Alarm_2);
	RegData[1].pRegistrationCmd = pRegistrationCmd = new AlarmRegistrationCmd(this, AlarmManager::Alarm_ID::Alarm_2);

	RegData[2].pDeregistrationCmd = pDeregistrationCmd = new AlarmDeregistrationCmd(this, AlarmManager::Alarm_ID::Alarm_3);
	RegData[2].pRegistrationCmd = pRegistrationCmd = new AlarmRegistrationCmd(this, AlarmManager::Alarm_ID::Alarm_3);

	RegData[3].pDeregistrationCmd = pDeregistrationCmd = new AlarmDeregistrationCmd(this, AlarmManager::Alarm_ID::Alarm_4);
	RegData[3].pRegistrationCmd = pRegistrationCmd = new AlarmRegistrationCmd(this, AlarmManager::Alarm_ID::Alarm_4);

	RegData[4].pDeregistrationCmd = pDeregistrationCmd = new AlarmDeregistrationCmd(this, AlarmManager::Alarm_ID::Alarm_5);
	RegData[4].pRegistrationCmd = pRegistrationCmd = new AlarmRegistrationCmd(this, AlarmManager::Alarm_ID::Alarm_5);
}

Alarmable::~Alarmable()
{
	delete RegData[0].pDeregistrationCmd;
	delete RegData[0].pRegistrationCmd;

	delete RegData[1].pDeregistrationCmd;
	delete RegData[1].pRegistrationCmd;

	delete RegData[2].pDeregistrationCmd;
	delete RegData[2].pRegistrationCmd;

	delete RegData[3].pDeregistrationCmd;
	delete RegData[3].pRegistrationCmd;


	delete RegData[4].pDeregistrationCmd;
	delete RegData[4].pRegistrationCmd;
}

/// <summary>
/// \brief  Registers an Alarm within the GameObject, allowing timed events to occur
/// \ingroup GAMEOBJECTCONTROL
/// 
/// In order to register an Alarm the user must use this method and detail the alarm's time and ID (whether it will be Alarm 1, 2, or 3)
/// \code
/// Alarmable::SubmitAlarmRegistration(float t, AlarmManager::Alarm_ID id)
/// \endcode
/// 
/// Now lets say the user entered SubmitAlarmRegistration(float 5, AlarmManager::Alarm_ID::Alarm_1)
/// <br>
/// <br>
/// This means Alarm_1 will go off in 5 seconds and be triggered in a user specified method like this:
/// <br>
/// (In this example I have a Turret that shoots a bullet every 5 seconds
/// \code
///	void Turret::Alarm1()
/// {
///		BulletFactory::CreateBullet(target->getPos(), Hworld * Matrix(TRANS, 0, 2, 0));
///		Alarmable::SubmitAlarmRegistration(5, AlarmManager::Alarm_ID::Alarm_1); //resets Alarm_1
/// }
/// \endcode
/// 
/// \note Alarmable::SubmitAlarmDeregistration(AlarmManager::Alarm_ID id) can be used in the exact same way in order to stop the Alarm
/// </summary>
void Alarmable::SubmitAlarmRegistration(float t, AlarmManager::Alarm_ID id)
{
	float time = t + TimeManager::GetTime();
	int idNum = (int)id;

	assert((int)id >= 0 && (int)id <= 4 && "Only 3 alarms allowed!");
	if (RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED)
	{
		RegData[idNum].pRegistrationCmd->setTime(time);
		SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), RegData[idNum].pRegistrationCmd);

		RegData[idNum].RegStateCurr = RegistrationState::PENDING_REGISTRATION;
	}
}

void Alarmable::SubmitAlarmDeregistration(AlarmManager::Alarm_ID id)
{
	int idNum = (int)id;
	if (RegData[idNum].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		//assert(RegData[idNum].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), RegData[idNum].pDeregistrationCmd);

		RegData[idNum].RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void Alarmable::AlarmRegistration(float t, AlarmManager::Alarm_ID id)
{
	int idNum = (int)id;
	assert(RegData[idNum].RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Xables::Register(t, this, id, RegData[idNum].pMyDeleteRef, SceneManager::getCurrentScene());

	RegData[idNum].RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::AlarmDeregistration(AlarmManager::Alarm_ID id)
{
	int idNum = (int)id;
	assert(RegData[idNum].RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Xables::Deregister(SceneManager::getCurrentScene(), RegData[idNum].pMyDeleteRef);

	RegData[idNum].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::TriggerAlarm(AlarmManager::Alarm_ID id)
{
	int idNum = (int)id;
	RegData[idNum].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	switch (id)
	{
	case AlarmManager::Alarm_ID::Alarm_1:
		this->Alarm1();
		break;
	case AlarmManager::Alarm_ID::Alarm_2:
		this->Alarm2();
		break;
	case AlarmManager::Alarm_ID::Alarm_3:
		this->Alarm3();
		break;
	case AlarmManager::Alarm_ID::Alarm_4:
		this->Alarm4();
		break;
	case AlarmManager::Alarm_ID::Alarm_5:
		this->Alarm5();
		break;
	};

}

void Alarmable::SetOffAlarm(AlarmManager::Alarm_ID id)
{
	if (RegData[(int)id].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorney::Xables::SetOff(SceneManager::getCurrentScene(), id);
	}
}

void Alarmable::setDelete(const AlarmManager::StorageListRef& ref, AlarmManager::Alarm_ID id)
{
	int idNum = (int)id;
	RegData[idNum].pMyDeleteRef = ref;
}
