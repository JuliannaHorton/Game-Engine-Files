#pragma once

#ifndef _CollisionDeregistrationCmd
#define _CollisionDeregistrationCmd

#include "SceneCommand.h"
class Collidable;

class CollisionDeregistrationCmd : public SceneCommand
{
public:

	CollisionDeregistrationCmd() = default;
	CollisionDeregistrationCmd(const CollisionDeregistrationCmd&) = delete;
	CollisionDeregistrationCmd& operator=(const CollisionDeregistrationCmd&) = delete;
	~CollisionDeregistrationCmd() = default; //This might be bad

	CollisionDeregistrationCmd(Collidable* Col) : ptrCol(Col) {};

	virtual void execute();

private:

	Collidable* ptrCol;
};


#endif _CollisionDeregistrationCmd