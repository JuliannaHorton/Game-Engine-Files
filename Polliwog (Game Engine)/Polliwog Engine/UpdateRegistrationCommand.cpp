#include "UpdateRegistrationCommand.h"
#include "UpdateAttorney.h"

void UpdateRegistrationCmd::execute()
{
	UpdateAttorney::Registration::SceneRegistration(ptrUp);
}