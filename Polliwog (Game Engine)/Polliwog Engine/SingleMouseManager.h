#pragma once

#ifndef _SingleMouseManager
#define _SingleMouseManager

#include <list>

#include "Inputable.h"

class SingleMouseManager
{
private:
	FROG_MOUSE key; //This is the key its managing

	using keyPressCol = std::list<Inputable*>; //Inputables with released
	keyPressCol PressCol;

	using keyReleaseCol = std::list<Inputable*>;
	keyReleaseCol ReleaseCol;

	bool pressed;

public:
	SingleMouseManager();
	SingleMouseManager(const SingleMouseManager&) = delete;
	SingleMouseManager& operator=(const SingleMouseManager&) = delete;
	~SingleMouseManager() = default;

	SingleMouseManager(FROG_MOUSE k);

	void Deregister(Inputable* a, EVENT_TYPE e);
	void Register(Inputable* a, EVENT_TYPE e);
	void ProcessKeyEvent();

};

#endif _SingleMouseManager
