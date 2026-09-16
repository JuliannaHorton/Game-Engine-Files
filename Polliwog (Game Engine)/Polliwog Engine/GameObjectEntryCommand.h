#pragma once

#ifndef _GameObjectEntryCmd
#define _GameObjectEntryCmd

#include "SceneCommand.h"
class GameObject;

class GameObjectEntryCmd : public SceneCommand
{
public:

	GameObjectEntryCmd() = default;
	GameObjectEntryCmd(const GameObjectEntryCmd&) = delete;
	GameObjectEntryCmd& operator=(const GameObjectEntryCmd&) = delete;
	~GameObjectEntryCmd() = default; //This might be bad

	GameObjectEntryCmd(GameObject* p) : ptrGO(p) {};

	virtual void execute();

private:

	GameObject* ptrGO;
};


#endif _GameObjectEntryCmd