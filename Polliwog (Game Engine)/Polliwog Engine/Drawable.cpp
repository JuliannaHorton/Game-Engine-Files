#include "Drawable.h"
#include "SceneAttorney.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeregistrationCommand.h"


//
// All needed registers stored, so that its not calling new with every command
//
Drawable::Drawable()
{
	pRegistrationCmd = new DrawRegistrationCmd(this);
	pDeregistrationCmd = new DrawDeregistrationCmd(this);
}

Drawable::~Drawable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
}

/// <summary>
/// \brief Registers a GameObject as an Drawable, allowing the object to be rendered
/// \ingroup GAMEOBJECTCONTROL
/// 
/// In order to register a Game Object as Drawable the user must use this method
/// \code
/// Drawable::SubmitDrawRegistration()
/// \endcode
/// 
/// And add this method to the class:
/// \code
/// virtual void Draw();
/// \endcode
/// 
/// Once finished a user can begin using Draw() similar to this:
/// <br>
/// In this example I am rendering my Tank GameObject
/// \code
///	void Tank::Draw()
///	{
///		myTank->Render(SceneManager::getCurrentScene()->getCamera());
///	{
/// \endcode
/// 
/// \note Drawable::SubmitDrawRegistration() can be used in the exact same way in order to stop the Game Object from drawing
/// </summary>
void Drawable::SubmitDrawRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pRegistrationCmd);

	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	if (RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		//assert(RegData[idNum].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pDeregistrationCmd);

		RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void Drawable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Xables::Register(this, pMyDeleteRef, SceneManager::getCurrentScene());

	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Xables::Deregister(pMyDeleteRef, SceneManager::getCurrentScene());

	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::setDelete(const DrawManager::StorageListRef& ref)
{
	pMyDeleteRef = ref;
}