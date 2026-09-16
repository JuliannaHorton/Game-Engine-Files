#include "Inputable.h"
#include "SceneAttorney.h"
#include "SceneManager.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"
#include "MouseInputRegistrationCommand.h"
#include "MouseInputDeregistrationCommand.h"
#include "KeyboardManager.h"

Inputable::~Inputable()
{
	//I feel like there's an easier way of doing this

	for (auto& press : KeyMap)
	{
		if (press.second.pRegistrationCmd != nullptr)
		{
			delete press.second.pRegistrationCmd;
		}
		if (press.second.pDeregistrationCmd != nullptr)
		{
			delete press.second.pDeregistrationCmd;
		}
	}

	for (auto& press : MouseMap)
	{
		if (press.second.pRegistrationCmd != nullptr)
		{
			delete press.second.pRegistrationCmd;
		}
		if (press.second.pDeregistrationCmd != nullptr)
		{
			delete press.second.pDeregistrationCmd;
		}
	}
}


/// <summary>
/// \brief Registers a GameObject as an Inputable, allowing Press and Release inputs
/// \ingroup GAMEOBJECTCONTROL
/// 
/// In order to register a Game Object as Inputable the user must use this method and detail 
/// which Key they want and whether it will be a 'Press' or 'Release' event
/// \code
/// Inputable::SubmitRegistration(AZUL_KEY k, EVENT_TYPE e)
/// \endcode
/// 
/// And add this method to the class:
/// \code
/// virtual void KeyPressed(AZUL_KEY k);
/// \endcode
/// 
/// Once finished a user can begin using Update() similar to this:
/// <br>
/// In this example I am checking if the 0 key was pressed, if so it switches to TankScene
/// \code
///	void Frigate::KeyPressed(AZUL_KEY k)
///	{
///		if (k == AZUL_KEY::KEY_0)
///		{
///			SceneManager::setNextScene(TankScene);
///		}
///	{
/// \endcode
/// 
/// \note Inputable::SubmitDeregistration can be used in the exact same way in order to stop the Game Object from updating
/// </summary>
void Inputable::SubmitRegistration(FROG_KEY k, EVENT_TYPE e)
{
	assert(KeyMap[k].RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	if (KeyMap[k].pRegistrationCmd == nullptr)
	{
		KeyMap[k].pRegistrationCmd = new InputRegistrationCmd(this);
		KeyMap[k].pDeregistrationCmd = new InputDeregistrationCmd(this);
	}

	KeyMap[k].pRegistrationCmd->setKey(k);
	KeyMap[k].pRegistrationCmd->setEvent(e);

	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), KeyMap[k].pRegistrationCmd);

	KeyMap[k].RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Inputable::SubmitDeregistration(FROG_KEY k, EVENT_TYPE e)
{
	assert(KeyMap[k].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	KeyMap[k].pDeregistrationCmd->setKey(k);
	KeyMap[k].pDeregistrationCmd->setEvent(e);

	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), KeyMap[k].pDeregistrationCmd);

	KeyMap[k].RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Inputable::SceneRegistration(FROG_KEY k, EVENT_TYPE e)
{
	assert(KeyMap[k].RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Xables::Register(this, k, e, SceneManager::getCurrentScene());

	KeyMap[k].RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(FROG_KEY k, EVENT_TYPE e)
{
	assert(KeyMap[k].RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Xables::Deregister(this, k, e, SceneManager::getCurrentScene());

	KeyMap[k].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}


//
// Mouse Keys
//

/// <summary>
/// \brief Registers a GameObject as an Inputable, allowing Press and Release inputs
/// \ingroup GAMEOBJECTCONTROL
/// 
/// In order to register a Game Object as Inputable the user must use this method and detail 
/// which Key they want and whether it will be a 'Press' or 'Release' event
/// \code
/// Inputable::SubmitRegistration(AZUL_MOUSE k, EVENT_TYPE e)
/// \endcode
/// 
/// And add this method to the class:
/// \code
/// virtual void KeyPressed(AZUL_MOUSE k);
/// \endcode
/// 
/// Once finished a user can begin using Update() similar to this:
/// <br>
/// In this example I am checking if the 0 key was pressed, if so it switches to TankScene
/// \code
///	void Frigate::KeyPressed(AZUL_MOUSE k)
///	{
/// 	case AZUL_MOUSE::BUTTON_LEFT: //Fireing Bullets
///		if (k == AZUL_MOUSE::BUTTON_LEFT)
///		{
///			myTank->Shoot();
///		}
///	{
/// \endcode
/// 
/// \note Inputable::SubmitDeregistration can be used in the exact same way in order to stop the Game Object from updating
/// </summary>
void Inputable::SubmitRegistration(FROG_MOUSE k, EVENT_TYPE e)
{
	assert(MouseMap[k].RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);

	if (MouseMap[k].pRegistrationCmd == nullptr)
	{
		MouseMap[k].pRegistrationCmd = new MouseInputRegistrationCmd(this);
		MouseMap[k].pDeregistrationCmd = new MouseInputDeregistrationCmd(this);
	}

	MouseMap[k].pRegistrationCmd->setKey(k);
	MouseMap[k].pRegistrationCmd->setEvent(e);

	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), MouseMap[k].pRegistrationCmd);

	MouseMap[k].RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Inputable::SubmitDeregistration(FROG_MOUSE k, EVENT_TYPE e)
{
	assert(MouseMap[k].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);

	MouseMap[k].pDeregistrationCmd->setKey(k);
	MouseMap[k].pDeregistrationCmd->setEvent(e);

	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), MouseMap[k].pDeregistrationCmd);

	MouseMap[k].RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
}

void Inputable::SceneRegistration(FROG_MOUSE k, EVENT_TYPE e)
{
	assert(MouseMap[k].RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Xables::Register(this, k, e, SceneManager::getCurrentScene());

	MouseMap[k].RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::SceneDeregistration(FROG_MOUSE k, EVENT_TYPE e)
{
	assert(MouseMap[k].RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Xables::Deregister(this, k, e, SceneManager::getCurrentScene());

	MouseMap[k].RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}
