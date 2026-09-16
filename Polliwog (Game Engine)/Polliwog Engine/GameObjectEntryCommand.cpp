#include "GameObjectEntryCommand.h"
#include "GOAttorney.h"

void GameObjectEntryCmd::execute()
{
	GOAttorney::Registration::ConnectToScene(ptrGO);
}