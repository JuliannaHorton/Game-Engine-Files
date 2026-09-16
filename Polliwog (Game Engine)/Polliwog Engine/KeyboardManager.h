#pragma once

#ifndef _KeyboardManager
#define _KeyboardManager

#include <map>
#include "EventType.h"
#include "../Keyboard.h"

class Inputable;
class SingleKeyManager;

class KeyboardManager
{
private:
	// Data Structure: Hashmap
	using MapKey = std::map<FROG_KEY, SingleKeyManager*>;
	MapKey KeyList;

public:
	KeyboardManager() = default;
	KeyboardManager(const KeyboardManager&) = delete;
	KeyboardManager& operator=(const KeyboardManager&) = delete;
	~KeyboardManager();

	//
	// Single-Key Manager Registration ---> Scene Registration
	//
	void Register(Inputable* input, FROG_KEY k, EVENT_TYPE e);
	void Deregister(Inputable* input, FROG_KEY k, EVENT_TYPE e);
	void ProcessKeyEvents();

};

#endif _KeyboardManager
