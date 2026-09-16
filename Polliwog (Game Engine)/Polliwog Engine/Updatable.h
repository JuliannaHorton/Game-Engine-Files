#ifndef _Updatable
#define _Updatable

#include "UpdateManager.h"
#include "SceneManager.h"
#include "RegistrationState.h"

class UpdateRegistrationCmd;
class UpdateDeregistrationCmd;

class Updatable
{
	friend class UpdateAttorney;
public:
	Updatable();
	Updatable(const Updatable&) = delete;
	Updatable& operator=(const Updatable&) = delete;
	virtual ~Updatable();

	//
	// User Registration and Deregistration methods
	//
	void SubmitUpdateRegistration();
	void SubmitUpdateDeregistration();

private:
	UpdateManager::StorageListRef pMyDeleteRef; //Reference for Deletion
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED; //Registration State

	//
	// Commands to be used by the Scene's Command Pattern
	//
	UpdateRegistrationCmd* pRegistrationCmd;
	UpdateDeregistrationCmd* pDeregistrationCmd;

	//
	// Scene Registration and Deregistrations fro both Keyboard and Mouse control
	//
	void SceneRegistration();
	void SceneDeregistration();

	void setDelete(const UpdateManager::StorageListRef& ref);

	virtual void Update() {};
};


#endif _Updatable