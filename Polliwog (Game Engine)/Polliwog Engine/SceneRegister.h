#pragma once

#ifndef _SceneRegister
#define _SceneRegister

#include "SceneCommand.h"
#include <list>
#include <queue>

class SceneRegister
{
public:

	SceneRegister() = default;
	SceneRegister(const SceneRegister&) = delete;
	SceneRegister& operator=(const SceneRegister&) = delete;
	~SceneRegister() = default; //This might be bad

	void addCommand(SceneCommand* cmd);
	void executeCommands();

private:
	using StorageList = std::queue<SceneCommand*>;
	StorageList myCommands;

};


#endif _SceneRegister