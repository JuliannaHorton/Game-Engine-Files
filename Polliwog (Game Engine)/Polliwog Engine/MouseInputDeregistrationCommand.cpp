#include "MouseInputDeregistrationCommand.h"
#include "Inputable.h"
#include "InputAttorney.h"

void MouseInputDeregistrationCmd::execute()
{
	InputAttorney::MouseRegistration::SceneDeregistration(ptrInput, key, event);
}

void MouseInputDeregistrationCmd::setKey(FROG_MOUSE k)
{
	key = k;
}

void MouseInputDeregistrationCmd::setEvent(EVENT_TYPE e)
{
	event = e;
}