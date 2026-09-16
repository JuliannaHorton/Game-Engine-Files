#include "InputDeregistrationCommand.h"
#include "Inputable.h"
#include "InputAttorney.h"

void InputDeregistrationCmd::execute()
{
	InputAttorney::Registration::SceneDeregistration(ptrInput, key, event);
}

void InputDeregistrationCmd::setKey(FROG_KEY k)
{
	key = k;
}

void InputDeregistrationCmd::setEvent(EVENT_TYPE e)
{
	event = e;
}