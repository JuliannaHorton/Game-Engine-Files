#include "AlarmRegistrationCommand.h"
#include "AlarmAttorney.h"

void AlarmRegistrationCmd::execute()
{
	AlarmAttorney::Registration::AlarmRegistration(time, ptrAlert, ID);
}

void AlarmRegistrationCmd::setTime(float t)
{
	time = t;
}

