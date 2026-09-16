#include "GameObject.h"
#include "SceneAttorney.h"
#include "GameObjectExitCommand.h"
#include "GameObjectEntryCommand.h"


/// <summary>
/// \brief Base class for all in-game entities, providing rendering,
/// updating, input handling, and timed event support.
/// \ingroup IMPORTANTCLASSES
///
/// GameObject serves as the foundational entity type within the engine.
/// It derives from Drawable, Updatable, Inputable, and Alarmable to enable
/// rendering, updates, input processing, and alarm-driven events.
///
/// These capabilities are managed through a registration/deregistration
/// system, allowing each GameObject to selectively participate only in the
/// subsystems it requires.
/// 
/// GameObject also maintains its own registration mechanism to control
/// scene entry and removal, ensuring proper integration with the scene
/// lifecycle.
/// </summary>
/// 
GameObject::GameObject()
{
	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	pRegCmd = new GameObjectEntryCmd(this);
	pDeregCmd = new GameObjectExitCmd(this);
}

GameObject::~GameObject()
{
	delete pRegCmd;
	delete pDeregCmd;
}

//Registration and Deregistration
	/// <summary>
	/// \brief Signals that an object will be entering the Scene
	/// \ingroup GAMEOBJECTCONTROL
	///
	/// Submits a request for this GameObject to be re-enter the scene after previously being removed.
	/// 
	/// For Example it could be used within a Factory:
	/// <br>
	/// Here I am utilizing the Submit entery to push an already created bullet back into the Scene
	/// \code
	/// Bullet* BulletFactory::privCreateBullet(Matrix rot, Matrix pos)
	///{
	///		Bullet* b;
	///		b = myBulletPool->GetBullet();
	///
	///		b->Initialize(rot, pos); //Provide it with current peramitters 
	///		b->SubmitEntry(); //Return the bullet to the scene
	///
	///		return b;
	///	}
	/// \endcode
	/// </summary>
void GameObject::SubmitEntry()
{
	if (RegStateCurr != RegistrationState::CURRENTLY_DEREGISTERED)
	{
		assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	}
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pRegCmd);

	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}
/// <summary>
/// \brief Signals that an object will be exiting the Scene
/// \ingroup GAMEOBJECTCONTROL
///
/// Submits a request for this GameObject to be removed from the Scene.
/// 
/// For Example it could be used to remove an object after a collision:
/// <br>
/// Here I am removing the bullet after contact with the Tank
/// \code
/// void Bullet::Collision(Tank*)
///	{
///		DebugMsg::out("Collision Bullet with Tank\n");
///		SubmitAlarmDeregistration(AlarmManager::Alarm_ID::Alarm_1);
///
///		SubmitExit(); //removes bullet
///	}
/// \endcode
/// </summary>
void GameObject::SubmitExit()
{
	if (RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		assert(RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pDeregCmd);

		RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void GameObject::ConnectToScene()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	this->SceneEntry(); // user method

	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::DisconnectFromScene()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	this->SceneExit(); // user method

	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

