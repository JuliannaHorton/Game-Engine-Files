#ifndef _GameObject
#define _GameObject

#include "Drawable.h"
#include "Updatable.h"
#include "Alarmable.h"
#include "Inputable.h"
#include "Collidable.h"
//#include "AzulCore.h"

#include "RegistrationState.h"

class GameObjectExitCmd;
class GameObjectEntryCmd;
class GOAttorney;

class GameObject : public Drawable, public Updatable, public Alarmable, public Inputable, public Collidable
{
	friend GOAttorney;
public:
	GameObject();
	GameObject(const GameObject&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	virtual ~GameObject();

	//
	// Used by the User
	//
	void SubmitEntry();
	void SubmitExit();

	//Allows for easy access to any game objects postion
	//Matrix getPos() { return World; };

private:

	//
	// Registration commands for a GameObject leaving and entering the scene
	//
	GameObjectEntryCmd* pRegCmd;
	GameObjectExitCmd* pDeregCmd;

	RegistrationState RegStateCurr; //Registration State

	//
	// Works with the scene to for easy insertion or removal from a scene
	//
	void ConnectToScene();
	void DisconnectFromScene();
	virtual void SceneEntry() {};
	virtual void SceneExit() {};

};


#endif _GameObject