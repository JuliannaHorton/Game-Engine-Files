#ifndef _Drawable
#define _Drawable

#include "DrawManager.h"
#include "SceneManager.h"
#include "RegistrationState.h"

class DrawRegistrationCmd;
class DrawDeregistrationCmd;

class Drawable
{
	friend class DrawAttorney;
public:
	Drawable();
	Drawable(const Drawable&) = delete;
	Drawable& operator=(const Drawable&) = delete;
	virtual ~Drawable();

	//
	// User Registration and Deregistration methods
	//
	void SubmitDrawRegistration();
	void SubmitDrawDeregistration();

private:
	DrawManager::StorageListRef pMyDeleteRef; //Stored Reference for easy deletion
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED; //Registration State

	//
	//Commands to be processed by the Scene's Command Pattern
	//
	DrawRegistrationCmd* pRegistrationCmd;
	DrawDeregistrationCmd* pDeregistrationCmd;

	//Two different Draws
	virtual void Draw() {};
	virtual void Draw2D() {};

	//
	// Scene Registration and Deregistrations 
	//
	void SceneRegistration();
	void SceneDeregistration();

	void setDelete(const DrawManager::StorageListRef& ref);
};


#endif _Drawable