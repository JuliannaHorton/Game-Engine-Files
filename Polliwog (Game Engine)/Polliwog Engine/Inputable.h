#pragma once

#ifndef _Inputable
#define _Inputable

#include "RegistrationState.h"
#include "EventType.h"
#include "../Keyboard.h"
#include "../Mouse.h"
#include <map>

class InputRegistrationCmd;
class InputDeregistrationCmd;
class MouseInputRegistrationCmd;
class MouseInputDeregistrationCmd;

class Inputable
{
public:
	Inputable() = default;
	Inputable(const Inputable&) = delete;
	Inputable& operator=(const Inputable&) = delete;
	virtual ~Inputable();

	//
	// User Registration and Deregistration methods
	//
	void SubmitRegistration(FROG_KEY k, EVENT_TYPE e);
	void SubmitDeregistration(FROG_KEY k, EVENT_TYPE e);
	void SubmitRegistration(FROG_MOUSE k, EVENT_TYPE e);
	void SubmitDeregistration(FROG_MOUSE k, EVENT_TYPE e);

	friend class InputAttorney;

private:
	//InputManager::StorageListRef pMyDeleteRef;
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;

	InputRegistrationCmd* pRegistrationCmd;
	InputDeregistrationCmd* pDeregistrationCmd;


	//
	// Scene Registration and Deregistrations for both Keyboard and Mouse control
	//
	void SceneRegistration(FROG_KEY k, EVENT_TYPE e);
	void SceneDeregistration(FROG_KEY k, EVENT_TYPE e);
	void SceneRegistration(FROG_MOUSE k, EVENT_TYPE e);
	void SceneDeregistration(FROG_MOUSE k, EVENT_TYPE e);

	virtual void KeyPressed(FROG_KEY k) { k = FROG_KEY::KEY_0; };
	virtual void KeyReleased(FROG_KEY k) { k = FROG_KEY::KEY_0; };
	virtual void KeyPressed(FROG_MOUSE k) { k = FROG_MOUSE::BUTTON_1; };
	virtual void KeyReleased(FROG_MOUSE k) { k = FROG_MOUSE::BUTTON_1; };

	//
	// Registration data stored with each kry
	//
	struct RegistrationData
	{
		RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		InputRegistrationCmd* pRegistrationCmd = nullptr;
		InputDeregistrationCmd* pDeregistrationCmd = nullptr;
	};

	struct MouseRegistrationData
	{
		RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
		MouseInputRegistrationCmd* pRegistrationCmd = nullptr;
		MouseInputDeregistrationCmd* pDeregistrationCmd = nullptr;
	};

	//Data Structure: HashMaps
	using MapKey = std::map<FROG_KEY, RegistrationData>;
	MapKey KeyMap;
	using MapMouse = std::map<FROG_MOUSE, MouseRegistrationData>;
	MapMouse MouseMap;

	//I will need a map for multiple keys, but I want to test 1 key registration first. Key = key, 
};


#endif _Inputable