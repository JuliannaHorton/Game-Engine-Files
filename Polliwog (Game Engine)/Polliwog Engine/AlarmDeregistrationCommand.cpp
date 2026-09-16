#include "AlarmDeregistrationCommand.h"
#include "AlarmAttorney.h"

void AlarmDeregistrationCmd::execute()
{
	AlarmAttorney::Registration::AlarmDeregistration(ptrAlert, ID);
}