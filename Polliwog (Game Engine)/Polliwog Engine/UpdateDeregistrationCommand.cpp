#include "UpdateDeregistrationCommand.h"
#include "UpdateAttorney.h"

void UpdateDeregistrationCmd::execute()
{
	UpdateAttorney::Registration::SceneDeregistration(ptrUp);
}