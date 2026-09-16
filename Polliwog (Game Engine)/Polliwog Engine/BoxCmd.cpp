#include "BoxCmd.h"
#include "VisualAttorney.h"

void BoxCmd::execute()
{
	VisualAttorney::Box::RenderBox(World, Color);
}

void BoxCmd::returnCmd()
{
	VisualAttorney::Box::ReturnBoxCmd(this);
}