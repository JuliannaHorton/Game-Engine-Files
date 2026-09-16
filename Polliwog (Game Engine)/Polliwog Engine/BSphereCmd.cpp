#include "BSphereCmd.h"
#include "VisualAttorney.h"

void BSphereCmd::execute()
{
	VisualAttorney::Sphere::RenderBSphere(World, Color);
}

void BSphereCmd::returnCmd()
{
	VisualAttorney::Sphere::ReturnBSphereCmd(this);
}