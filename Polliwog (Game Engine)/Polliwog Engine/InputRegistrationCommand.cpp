#include "InputRegistrationCommand.h"
#include "Inputable.h"
#include "InputAttorney.h"

void InputRegistrationCmd::execute()
{
	InputAttorney::Registration::SceneRegistration(ptrInput, key, event);
}

void InputRegistrationCmd::setKey(FROG_KEY k)
{
	key = k;
}

void InputRegistrationCmd::setEvent(EVENT_TYPE e)
{
	event = e;
}