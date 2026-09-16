#pragma once

#ifndef _GameObjectExitCmd
#define _GameObjectExitCmd

#include "SceneCommand.h"
class GameObject;

class GameObjectExitCmd : public SceneCommand
{
public:

	GameObjectExitCmd() = default;
	GameObjectExitCmd(const GameObjectExitCmd&) = delete;
	GameObjectExitCmd& operator=(const GameObjectExitCmd&) = delete;
	~GameObjectExitCmd() = default; //This might be bad

	GameObjectExitCmd(GameObject* p) : ptrGO(p) {};

	virtual void execute();

private:

	GameObject* ptrGO;
};


#endif _GameObjectExitCmd