#pragma once

#ifndef _CollisionRegistrationCmd
#define _CollisionRegistrationCmd

#include "SceneCommand.h"
class Collidable;

class CollisionRegistrationCmd : public SceneCommand
{
public:

	CollisionRegistrationCmd() = default;
	CollisionRegistrationCmd(const CollisionRegistrationCmd&) = delete;
	CollisionRegistrationCmd& operator=(const CollisionRegistrationCmd&) = delete;
	~CollisionRegistrationCmd() = default; //This might be bad

	CollisionRegistrationCmd(Collidable* Col) : ptrCol(Col) {};

	virtual void execute();

private:

	Collidable* ptrCol;
};


#endif _CollisionRegistrationCmd