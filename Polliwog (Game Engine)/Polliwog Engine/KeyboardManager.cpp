#include "KeyboardManager.h"
#include "SingleKeyManager.h"
#include "Inputable.h"

void KeyboardManager::Register(Inputable* input, FROG_KEY k, EVENT_TYPE e)
{
	auto it = KeyList.find(k);

	if (it == KeyList.end())
	{
		SingleKeyManager* myKey = new SingleKeyManager(k);
		KeyList[k] = myKey;
		myKey->Register(input, e);
	}
	else
	{
		it->second->Register(input, e);
	}
}

void KeyboardManager::Deregister(Inputable* input, FROG_KEY k, EVENT_TYPE e)
{
	KeyList.find(k)->second->Deregister(input, e);
}

void KeyboardManager::ProcessKeyEvents()
{
	for (auto& KeyEvent : KeyList)
	{
		KeyEvent.second->ProcessKeyEvent();
	}
}

KeyboardManager::~KeyboardManager()
{
	for (auto& KeyEvent : KeyList)
	{
		delete KeyEvent.second;
	}
}