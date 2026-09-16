#pragma once

#ifndef _SceneManager
#define _SceneManager

#include "Scene.h"
#include <map>

class Camera;
class SceneChangeCmd;
class SceneChange;
class SceneChangeAction;
class SceneChangeNull;

class SceneManager
{
	friend class SceneManagerAttorney;
private:
	static SceneManager* ptrInstance;

	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	~SceneManager() = default;

	static SceneManager& Instance()
	{
		if (ptrInstance == nullptr)
			ptrInstance = new SceneManager();
		return *ptrInstance;
	};

	Scene* privGetCurrentScene();

	static Scene* currentScene;
	static SceneChange* myChange; //pointer to strategy pattern

	void privSetNextScene(Scene* nextScene);
	Terrain* privGetTerrain();
	static void ChangeScene(Scene* ns);

	//Deletes the current scene and cleans up singleton --- Called by Polliwog Engine
	void privDelete();
	static void Delete() { Instance().privDelete(); };

	//Calls the actual Scene's update and draw
	static void Draw();
	static void Update();

public:
	/// <summary>
	/// \brief Accesses the current Scene
	/// \ingroup SCENE
	///
	/// Using the SceneManager the User can access the current scene in order to privide access to
	/// the Scene's public methods, such as the Get/Set Camera functions
	/// <br>
	/// <br>
	/// For Example Rendering will require access to the Scene:
	/// <br>
	/// \code 
	/// void Tank::Draw()
	/// {
	/// 	myTank->Render(SceneManager::getCurrentScene()->getCamera());
	/// }
	/// \endcode
	/// 
	/// </summary>
	static Scene* getCurrentScene() { return Instance().privGetCurrentScene(); }; //returns the current scene

	/// <summary>
	/// \brief Sets a new Scene
	/// \ingroup SCENE
	///
	/// When the user creates a Scene they can switch to it via this function
	/// <br>
	/// <br>
	/// For Example this sets a new Scene:
	/// <br>
	/// \code 
	///	SceneManager::setNextScene(new TankScene());
	/// \endcode
	/// This will then automatically call the Initialize Function in the Scene.
	/// <br>
	/// It is up to the user to put objects in the Scene otherwise the Scene will be blank.
	/// <br>
	/// <br>
	/// Here is an exmaple of how a user may Intialize their Scene
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
	/// Put screenshot of Scene here!
	/// </summary>
	static void setNextScene(Scene* ns) { Instance().privSetNextScene(ns); }; //sets the next scene

	static Terrain* getTerrain() { return Instance().privGetTerrain(); }; //sets the next scene
};


#endif _SceneManager