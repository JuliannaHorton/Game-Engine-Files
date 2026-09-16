#include "GameObjectExitCommand.h"
#include "GOAttorney.h"

void GameObjectExitCmd::execute()
{
	GOAttorney::Registration::DisconnectFromScene(ptrGO);
}