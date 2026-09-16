#pragma once

#ifndef _CollisionTerrainCmd
#define _CollisionTerrainCmd

#include "CollisionTestCommand.h"

#include <list>

class Collidable;
class TRAIterator;

class CollisionDispatchBase;
class CollidableGroup;

class CollisionTerrainCmd : public CollisionTestCmd
{
public:
	CollisionTerrainCmd() = default; 
	CollisionTerrainCmd(const CollisionTerrainCmd&) = delete; 
	CollisionTerrainCmd& operator=(const CollisionTerrainCmd&) = delete;
	~CollisionTerrainCmd() = default;

	CollisionTerrainCmd(CollidableGroup* cg) : pG(cg){};

	virtual void execute();

private:
	CollidableGroup* pG;

	TRAIterator* ItCell = nullptr;



	using DifCollidableCollection = std::list<Collidable*>; //list for now, I'll look into the best type once I have a better idea of what I need
	DifCollidableCollection ColCollection;

};

#endif _CollisionTerrainCmd