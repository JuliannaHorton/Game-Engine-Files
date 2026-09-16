#pragma once

#ifndef _CollisionPairCmd
#define _CollisionPairCmd

#include "CollisionTestCommand.h"
#include <list>

class Collidable;

class CollisionDispatchBase;
class CollidableGroup;

class CollisionPairCmd : public CollisionTestCmd
{
public:
	CollisionPairCmd() = default;
	CollisionPairCmd(const CollisionPairCmd&) = delete;
	CollisionPairCmd& operator=(const CollisionPairCmd&) = delete;
	~CollisionPairCmd();

	CollisionPairCmd(CollidableGroup* cg1, CollidableGroup* cg2, CollisionDispatchBase* pDis) : pG1(cg1), pG2(cg2), pDispatch(pDis) {};

	virtual void execute();

private:
	CollisionDispatchBase* pDispatch;
	CollidableGroup* pG1;
	CollidableGroup* pG2;

	using DifCollidableCollection = std::list<Collidable*>; //list for now, I'll look into the best type once I have a better idea of what I need
	DifCollidableCollection ColCollection;

};

#endif _CollisionPairCmd