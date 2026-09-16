#pragma once

#ifndef _MouseManager
#define _MouseManager

#include <map>
#include "EventType.h"
#include "../Mouse.h"

class Inputable;
class SingleMouseManager;

class MouseManager
{
private:
	using MapKey = std::map<FROG_MOUSE, SingleMouseManager*>;
	MapKey KeyList;

public:
	MouseManager() = default;
	MouseManager(const MouseManager&) = delete;
	MouseManager& operator=(const MouseManager&) = delete;
	~MouseManager();

	//
	// Single-Key Manager Registration ---> Scene Registration
	//
	void Register(Inputable* input, FROG_MOUSE k, EVENT_TYPE e);
	void Deregister(Inputable* input, FROG_MOUSE k, EVENT_TYPE e);
	void ProcessKeyEvents();

};

#endif _MouseManager
