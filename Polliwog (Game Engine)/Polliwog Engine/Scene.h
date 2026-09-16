#pragma once

#ifndef _Scene
#define _Scene

#include "UpdateManager.h"
#include "DrawManager.h"
#include "AlarmManager.h"
#include "CollisionManager.h"
#include "KeyboardManager.h"
#include "CameraManager.h"
#include "MouseManager.h"
#include "TerrainManager.h"

#include "SceneRegister.h"

class SceneCommand;
class CameraManager;
class CollisionManager;
class Camera;
class Terrain;

class TerrainStrat;
class TerrainDraw;
class TerrainNull;

class Scene
{
	friend class SceneAttorney;
public:
	/// <summary>
	/// \brief Base class for all user defined scenes, allowing users to alternate between their defined stages or states of the game
	/// 
	/// \ingroup IMPORTANTCLASSES
	///
	/// The Scene class encapsulates a collection of user created objects, cameras, 
	/// menus, and any other user defined classes that are desired in user's game state.
	/// The Scene is also responsible for the intialization and deletion of the collection
	/// as the user swaps between different scenes
	/// <br>
	/// <br>
	/// For exmaple a Scene's Intialization may look like this:
	/// <br>
	/// Create the new Scene via the SceneManager:
	/// \code 
	///		SceneManager::setNextScene(new TankScene());
	/// \endcode
	/// Intialize will then automatically be called (although it is up to the user to 
	/// place the new objects in the Scene's Intialize method):
	/// \code
	/// void TankScene::Intialize()
	/// {
	///		myTank = new Tank();
	///		Tur1 = new TankTurret();
	///	    Tur1->setTarget(myTank);
	///     Plane = new WorldPlane("Grass");
	/// 
	///		TankSceneCamera = new TankCam(this, myTank);
	/// 
	///     SetCollisionPair<Tank, Bullet>();
	///  }
	/// \endcode
	///
	/// </summary>
	Scene();
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	virtual ~Scene();

	//User defined in their own scene
	virtual void Intialize() = 0;
	virtual void SceneEnd() = 0;

	Camera* getCamera();
	void setCamera(Camera* c);
	void resetCamera();
	Camera* get2DCamera();


	/// <summary>
	/// \brief Returns the Scene's set Terrain
	/// 
	/// \ingroup TERRAIN
	Terrain* getTerrain();

protected:

	// Standard Collision
	template< typename C1, typename C2>
	void SetCollisionPair()
	{
		myCollisions.SetCollisionPair<C1, C2>();
	}

	template< typename C1>
	void SetCollisionSelf()
	{
		myCollisions.SetCollisionSelf<C1>();
	}

	// Terrain Collision
	template< typename C1>
	void SetCollisionTerrain()
	{
		myCollisions.SetCollisionTerrain<C1>();
	}

	void SetTerrain(std::string name);

private:
	//
	// All X-Able Managers
	//
	// Used when calling Update and Draw within this Scene class in order for the 
	// stored X-Able values to be processed
	UpdateManager myUpdates;
	DrawManager myDrawings;
	AlarmManager myAlarms;
	CollisionManager myCollisions;
	KeyboardManager myInputs;
	MouseManager myMouseInputs;
	CameraManager myCamMan;

	SceneRegister myRegister;

	//
	// Update's and Draw's all the specified manager above --- Called by Polliwog Engine
	//
	void Update();
	void Draw();

	void SubmitCommand(SceneCommand* cmd);
	CollisionManager* getCollisionMgr();

	//
	// All the -isters for the x-ables
	//
	// Accessed by the SceneCommand center via the SceneAgent for Game Object's X-Ables to be 
	// stored and used in the game loop
	void Register(Updatable*, UpdateManager::StorageListRef& deleteMe);
	void Deregister(const UpdateManager::StorageListRef& ref);
	void Register(Drawable*, DrawManager::StorageListRef& deleteMe);
	void Deregister(const DrawManager::StorageListRef& ref);
	void Register(float t, Alarmable* Alert, AlarmManager::Alarm_ID id, AlarmManager::StorageListRef& deleteMe);
	void Deregister(const AlarmManager::StorageListRef& ref);
	void Register(Inputable* input, FROG_KEY k, EVENT_TYPE e);
	void Deregister(Inputable* input, FROG_KEY k, EVENT_TYPE e);
	void Register(Inputable* input, FROG_MOUSE k, EVENT_TYPE e);
	void Deregister(Inputable* input, FROG_MOUSE k, EVENT_TYPE e);

	void SetOffAlarm(AlarmManager::Alarm_ID id);

	Vect CamPos = Vect(0, 0, 0, 0);
	Vect CamDir = Vect(0, 0, 0, 0);

	Terrain* pTerrain;
	TerrainDraw* TDraw;
	TerrainStrat* TerrainD;
	TerrainNull* TNull;
};


#endif _Scene