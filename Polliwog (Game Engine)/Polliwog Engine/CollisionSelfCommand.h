#pragma once

#ifndef _CollisionSelfCmd
#define _CollisionSelfCmd

#include "CollisionTestCommand.h"

#include <list>

class Collidable;

class CollisionDispatchBase;
class CollidableGroup;

class CollisionSelfCmd : public CollisionTestCmd
{
public:
	CollisionSelfCmd() = default; //???
	CollisionSelfCmd(const CollisionSelfCmd&) = delete; //???
	CollisionSelfCmd& operator=(const CollisionSelfCmd&) = delete;
	~CollisionSelfCmd();

	CollisionSelfCmd(CollidableGroup* cg, CollisionDispatchBase* pDis) : pG(cg), pDispatch(pDis) {};

	virtual void execute();

private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG;

	using DifCollidableCollection = std::list<Collidable*>; //list for now, I'll look into the best type once I have a better idea of what I need
	DifCollidableCollection ColCollection;

};

#endif _CollisionSelfCmd