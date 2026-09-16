#include "TimeManager.h"
#include "TadpoleAttorney.h"
#include "FreezeTime.h"

TimeManager* TimeManager::ptrInstance = nullptr;

FreezeTime TimeManager::myFrzTime;

float TimeManager::currentTime = 0;
float TimeManager::frameTime = 0;
float TimeManager::previousTime = 0;


float TimeManager::privGetFrameTime()
{
	return frameTime;
}

float TimeManager::privGetTime()
{
	return currentTime;
}

void TimeManager::ProcessTime()
{
	previousTime = currentTime; //Same as last frame

	currentTime = myFrzTime.ComputeGameTime(previousTime);
	//currentTime = PolliwogAgent::Time::GetTime(); //Total time passed;

	frameTime = currentTime - previousTime; //Subtract this sys_Time by the previous sys_Time
}

//Called by the Polliwog Engine
void TimeManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}