#include "Updatable.h"
#include "SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeregistrationCommand.h"

Updatable::Updatable()
{
	pRegistrationCmd = new UpdateRegistrationCmd(this);
	pDeregistrationCmd = new UpdateDeregistrationCmd(this);

}

Updatable::~Updatable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

/// <summary>
/// \brief Registers a GameObject as an Updatable, allowing the object to be Updated each frame
/// \ingroup GAMEOBJECTCONTROL
/// 
/// In order to register a Game Object as Updatable the user must use this method:
/// \code
/// Updatable::SubmitUpdateRegistration();
/// \endcode
/// 
/// And add this method to the class:
/// \code
/// virtual void Update();
/// \endcode
/// 
/// Once finished a user can begin using Update() similar to this:
/// <br>
/// In this example I am using it for movement
/// \code
/// void Frigate::Update()
/// {
///		World = ShipScale * ShipRotTrans;
///		SpaceShip->SetWorld(World);
/// 
///		if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
///		{
///			ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
///		}
///		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
///		{
///			ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
///		}
///
///		if (Keyboard::GetKeyState(AZUL_KEY::KEY_Q))
///		{
///			Updatable::SubmitUpdateDeregistration();
///		}
///
///		Visualizer::ShowBSphere(GetBSphere(), Colors::Blue);
///		UpdateCollsionData(World);
/// }
/// \endcode
/// 
/// \note SubmitUpdateDeregistration can be used in the exact same way in order to stop the Game Object from updating
/// </summary>
void Updatable::SubmitUpdateRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pRegistrationCmd);

	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Updatable::SubmitUpdateDeregistration()
{
	if (RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		//assert(RegData[idNum].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pDeregistrationCmd);

		RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void Updatable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Xables::Register(this, pMyDeleteRef, SceneManager::getCurrentScene());

	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Updatable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Xables::Deregister(pMyDeleteRef, SceneManager::getCurrentScene());

	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

}

void Updatable::setDelete(const UpdateManager::StorageListRef& ref)
{
	pMyDeleteRef = ref;
}
