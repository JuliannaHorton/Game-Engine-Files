#include "SingleMouseManager.h"
#include "InputAttorney.h"

SingleMouseManager::SingleMouseManager()
{
	pressed = false;
	//Is this needed, since it needs to be assigned a key
}

SingleMouseManager::SingleMouseManager(FROG_MOUSE k)
{
	pressed = false;
	key = k;
}

void SingleMouseManager::Register(Inputable* a, EVENT_TYPE e)
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

void SingleMouseManager::Deregister(Inputable* a, EVENT_TYPE e)
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

void SingleMouseManager::ProcessKeyEvent()
{
	if (Mouse::GetMouseKeyState(key) && !pressed)
	{
		for (auto& press : PressCol)
		{
			InputAttorney::MousePressandRelease::KeyPressed(press, key);
		}
	}
	else if (!Mouse::GetMouseKeyState(key) && pressed)
	{
		for (auto& release : ReleaseCol)
		{
			InputAttorney::MousePressandRelease::KeyReleased(release, key);
		}
	}

	pressed = Mouse::GetMouseKeyState(key);
}