#include "Scene.h"
#include "SceneCommand.h"
#include "../Keyboard.h"
#include "../Mouse.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "Terrain.h"

#include "TerrainStrat.h"
#include "TerrainNull.h"
#include "TerrainDraw.h"


Scene::Scene()
{
	TDraw = new TerrainDraw();
	TNull = new TerrainNull();

	TerrainD = TNull;
}

Scene::~Scene()
{
	delete TDraw;
	delete TNull;
}

void Scene::Update()
{
	myRegister.executeCommands(); //Loops through all registered Commands --- MUST BE FIRST or else the below managers will not be processed

	myAlarms.ProcessAlarms();

	//PointLightManager::SendCamInfo(mCam->getCurrentCamera()->getViewMatrix(), mCam->getCurrentCamera()->getProjMatrix(), lightMode);
	//SpotLightManager::SendCamInfo(mCam->getCurrentCamera()->getViewMatrix(), mCam->getCurrentCamera()->getProjMatrix(), lightMode);

	myUpdates.ProcessElements();

	myInputs.ProcessKeyEvents();

	myMouseInputs.ProcessKeyEvents();

	myCollisions.ProcessCollisions();

}

void Scene::Draw()
{
	TerrainD->DrawTerrain(); //Either creates a terrain or does nothing, depending on the user's choice

	myDrawings.ProcessElements(); //Draws 3D object before 2D ones
}

void Scene::SubmitCommand(SceneCommand* cmd)
{
	myRegister.addCommand(cmd);
}

//Camera Access
Camera* Scene::getCamera()
{
	return myCamMan.getCurrentCamera();
}

/// <summary>
/// \brief Set Current Camera to a new Camera
/// \ingroup SCENE
///
/// If the user creates their own Camera they have the option to set it to the current Scene
/// <br>
/// <br>
/// Example of use:
/// <br>
/// \code 
/// <...>
/// myCam = new Camera(Camera::Type::PERSPECTIVE_3D);
/// myCam->setViewport(0, 0, 960, 540);
/// myCam->setPerspective(35.0f, float(960) / float(540), 1.0f, 5000.0f);
/// 
/// myCam->setOrientAndPosition(defaultCameraUp, lookAt3DCam, CamPos);
/// myCam->updateCamera();
/// ptrScene->setCamera(myCam); //User sets the Camera to the Scene
/// <...>
/// \endcode
/// </summary>
void Scene::setCamera(Camera* c)
{
	myCamMan.setCamera(c);
}

/// <summary>
/// \brief Returns a 2D Camera
/// \ingroup SCENE
///
/// This is used in the same was as the current Camera except for 2D objects, such as Sprites or Sprite Strings
/// 
/// </summary>
Camera* Scene::get2DCamera()
{
	return myCamMan.get2D();
}

/// <summary>
/// \brief Resets Camera to Default
/// \ingroup SCENE
///
/// If the user desires to switch back to the default camera after setting up a new one, they can use this function
/// <br>
/// <br>
/// For Example this switches back to the default camera after Q is pressed:
/// <br>
/// \code 
/// <...>
/// void TankCam::KeyPressed(AZUL_KEY k)
/// {
/// 	if (k == AZUL_KEY::KEY_Q)
/// 	{
/// 		ptrScene->resetCamera();
/// 	}
/// }
/// <...>
/// \endcode
/// </summary>
void Scene::resetCamera()
{
	myCamMan.resetCamera();
}

Terrain* Scene::getTerrain()
{
	return pTerrain;
}




//All of the registers and deregisters
void Scene::Register(Updatable* Up, UpdateManager::StorageListRef& deleteMe)
{
	myUpdates.Register(Up, deleteMe);
}

void Scene::Deregister(const DrawManager::StorageListRef& ref)
{
	myDrawings.Deregister(ref);
}

void Scene::Register(Drawable* Draw, DrawManager::StorageListRef& deleteMe)
{
	myDrawings.Register(Draw, deleteMe);
}

void Scene::Deregister(const UpdateManager::StorageListRef& ref)
{
	myUpdates.Deregister(ref);
}

void Scene::Register(float t, Alarmable* Alert, AlarmManager::Alarm_ID id, AlarmManager::StorageListRef& deleteMe)
{
	myAlarms.Register(t, Alert, id, deleteMe);
}

void Scene::Deregister(const AlarmManager::StorageListRef& ref)
{
	myAlarms.Deregister(ref);
}

void Scene::Register(Inputable* input, FROG_KEY k, EVENT_TYPE e)
{
	myInputs.Register(input, k, e);
}

void Scene::Deregister(Inputable* input, FROG_KEY k, EVENT_TYPE e)
{
	myInputs.Deregister(input, k, e);
}

void Scene::Register(Inputable* input, FROG_MOUSE k, EVENT_TYPE e)
{
	myMouseInputs.Register(input, k, e);
}

void Scene::Deregister(Inputable* input, FROG_MOUSE k, EVENT_TYPE e)
{
	myMouseInputs.Deregister(input, k, e);
}

void Scene::SetOffAlarm(AlarmManager::Alarm_ID id)
{
	myAlarms.setOff(id);
}

//
// Accessed by the Collidable class via the 'Scene Agent' in order to set up Collidable groups
//
CollisionManager* Scene::getCollisionMgr()
{
	return &myCollisions;
}



/// <summary>
/// \brief Sets the Scene's Terrain
/// \ingroup SCENE
/// \ingroup TERRAIN
///
/// If the user would like Terrain in their scene they would use this method to add it
/// <br>
/// <br>
/// For Example in the Engine's Load Resources method they could write this
///
/// \code 
/// <...>
///		TerrainManager::Load("MainTerrain", TextureManager::Get("test"), TextureManager::Get("Grass"), 36, 36, 1000, 60);
/// <...>
/// \endcode
/// <br>
/// Then inside the desired scence Intialized class, they would write this to finally Set the Terrain
/// <br>
/// \code 
/// <...>
/// 	SetTerrain("MainTerrain");
///     SetCollisionTerrain<Tank>();
/// <...>
/// \endcode
/// </summary>
void Scene::SetTerrain(std::string name)
{
	TerrainD = TDraw;
	pTerrain = TerrainManager::Get(name);
	TerrainD->setTerrain(pTerrain);
}
