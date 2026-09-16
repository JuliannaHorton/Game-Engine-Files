#include "SingleKeyManager.h"
#include "InputAttorney.h"

SingleKeyManager::SingleKeyManager()
{
	pressed = false;
}

SingleKeyManager::SingleKeyManager(FROG_KEY k)
{
	pressed = false;
	key = k;
}

void SingleKeyManager::Register(Inputable* a, EVENT_TYPE e)
{
	switch (e)
	{
	case EVENT_TYPE::Key_Press:
		PressCol.push_back(a);
		break;
	case EVENT_TYPE::Key_Release:
		ReleaseCol.push_back(a);
		break;
	};
}

void SingleKeyManager::Deregister(Inputable* a, EVENT_TYPE e)
{
	switch (e)
	{
	case EVENT_TYPE::Key_Press:
		PressCol.remove(a);
		break;
	case EVENT_TYPE::Key_Release:
		ReleaseCol.remove(a);
		break;
	};
}

void SingleKeyManager::ProcessKeyEvent()
{
	if (Keyboard::GetKeyboardState(key) && !pressed)
	{
		for (auto& press : PressCol)
		{
			InputAttorney::PressandRelease::KeyPressed(press, key);
		}
	}
	else if (!Keyboard::GetKeyboardState(key) && pressed)
	{
		for (auto& release : ReleaseCol)
		{
			InputAttorney::PressandRelease::KeyReleased(release, key);
		}
	}

	pressed = Keyboard::GetKeyboardState(key);
}