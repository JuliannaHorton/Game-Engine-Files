#include "CollisionRegistrationCommand.h"
#include "CollisionAttorney.h"

void CollisionRegistrationCmd::execute()
{
	CollisionAttorney::Registration::CollideRegistration(ptrCol);
}