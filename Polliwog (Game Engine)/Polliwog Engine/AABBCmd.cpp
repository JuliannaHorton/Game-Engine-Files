#include "AABBCmd.h"
#include "VisualAttorney.h"

void AABBCmd::execute()
{
	VisualAttorney::Box::RenderBox(World, Color);
}

void AABBCmd::returnCmd()
{
	VisualAttorney::Box::ReturnBoxCmd(this);
}