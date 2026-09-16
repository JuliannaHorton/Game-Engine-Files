#include "SceneManager.h"
#include "SceneAttorney.h"
#include "CameraManager.h"
#include "SceneChangeNull.h"
#include "SceneChangeAction.h"
#include "NullScene.h"
#include "Change.h"

SceneManager* SceneManager::ptrInstance = nullptr;
Scene* SceneManager::currentScene = nullptr;
SceneChange* SceneManager::myChange;

SceneManager::SceneManager()
{
	//Set default scene
	myChange = &Change::Null;
	currentScene = new SceneNull();
}

void SceneManager::Update()
{
	myChange->Action(); //Will either do nothing or change scene

	SceneAttorney::GameLoop::Update(currentScene); //Update Scene
}

void SceneManager::Draw()
{
	SceneAttorney::GameLoop::Draw(currentScene); //Draw Scene
}

Scene* SceneManager::privGetCurrentScene()
{
	return currentScene;
}

void SceneManager::privDelete()
{
	currentScene->SceneEnd(); //Scene Clean-up
	delete currentScene;

	delete ptrInstance;
	ptrInstance = nullptr;
}

void SceneManager::ChangeScene(Scene* s)
{
	//Remove old scene
	currentScene->SceneEnd();
	delete currentScene;

	//Set new scene
	currentScene = s;
	currentScene->Intialize();

	//Set strategy
	myChange = &Change::Null;
}

void SceneManager::privSetNextScene(Scene* nextScene)
{
	assert(currentScene != nullptr && "Your scene is null");
	assert(myChange != &Change::Action && "You cannot change a scene within the same frame as another scene changing (double-changing)");

	//Set Strategy Pattern
	myChange = &Change::Action;
	myChange->setScene(nextScene); //Sets a pointer to the scene for the strategy  pattern to use 
}

// We need one in the manager so that the Engine can have access to the User's set Terrain
Terrain* SceneManager::privGetTerrain()
{
	return currentScene->getTerrain();
}