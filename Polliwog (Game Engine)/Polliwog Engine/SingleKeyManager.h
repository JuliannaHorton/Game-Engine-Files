#pragma once

#ifndef _SingleKeyManager
#define _SingleKeyManager

#include <list>

#include "Inputable.h"

class SingleKeyManager
{
private:
	FROG_KEY key; //This is the key its managing

	//
	// Stores both Pressed and released Keys based on their requested event
	//
	using keyPressCol = std::list<Inputable*>;
	keyPressCol PressCol;

	using keyReleaseCol = std::list<Inputable*>;
	keyReleaseCol ReleaseCol;

	bool pressed;

public:
	SingleKeyManager();
	SingleKeyManager(const SingleKeyManager&) = delete;
	SingleKeyManager& operator=(const SingleKeyManager&) = delete;
	~SingleKeyManager() = default;

	SingleKeyManager(FROG_KEY k);

	//Now Scene Registration
	void Deregister(Inputable* a, EVENT_TYPE e);
	void Register(Inputable* a, EVENT_TYPE e);
	void ProcessKeyEvent();

};

#endif _SingleKeyManager
