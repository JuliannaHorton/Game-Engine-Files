#include "DrawDeregistrationCommand.h"
#include "DrawAttorney.h"

void DrawDeregistrationCmd::execute()
{
	DrawAttorney::Registration::SceneDeregistration(ptrDraw);
}