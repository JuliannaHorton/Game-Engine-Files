#include "SceneChangeAction.h"
#include "SceneManagerAttorney.h"
#include "Scene.h"

void SceneChangeAction::Action()
{
	SceneManagerAttorney::SceneChange::ChangeScene(ptrScene);
}