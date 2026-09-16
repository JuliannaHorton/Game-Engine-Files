#include "CollisionDeregistrationCommand.h"
#include "CollisionAttorney.h"

void CollisionDeregistrationCmd::execute()
{
	CollisionAttorney::Registration::CollideDeregistration(ptrCol);
}