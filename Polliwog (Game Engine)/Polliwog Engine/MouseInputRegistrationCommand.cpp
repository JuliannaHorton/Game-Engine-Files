#include "MouseInputRegistrationCommand.h"
#include "Inputable.h"
#include "InputAttorney.h"

void MouseInputRegistrationCmd::execute()
{
	InputAttorney::MouseRegistration::SceneRegistration(ptrInput, key, event);
}

void MouseInputRegistrationCmd::setKey(FROG_MOUSE k)
{
	key = k;
}

void MouseInputRegistrationCmd::setEvent(EVENT_TYPE e)
{
	event = e;
}