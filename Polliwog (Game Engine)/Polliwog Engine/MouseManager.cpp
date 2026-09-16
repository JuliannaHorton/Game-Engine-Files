#include "MouseManager.h"
#include "SingleMouseManager.h"
#include "Inputable.h"

void MouseManager::Register(Inputable* input, FROG_MOUSE k, EVENT_TYPE e)
{
	auto it = KeyList.find(k);

	if (it == KeyList.end())
	{
		SingleMouseManager* myKey = new SingleMouseManager(k);
		KeyList[k] = myKey;
		myKey->Register(input, e);
	}
	else
	{
		it->second->Register(input, e);
	}
}

void MouseManager::Deregister(Inputable* input, FROG_MOUSE k, EVENT_TYPE e)
{
	KeyList.find(k)->second->Deregister(input, e);
}

void MouseManager::ProcessKeyEvents()
{
	for (auto& KeyEvent : KeyList)
	{
		KeyEvent.second->ProcessKeyEvent();
	}
}

MouseManager::~MouseManager()
{
	for (auto& KeyEvent : KeyList)
	{
		delete KeyEvent.second;
	}
}