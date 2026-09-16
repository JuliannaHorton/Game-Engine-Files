#include "DrawRegistrationCommand.h"
#include "DrawAttorney.h"

void DrawRegistrationCmd::execute()
{
	DrawAttorney::Registration::SceneRegistration(ptrDraw);
}