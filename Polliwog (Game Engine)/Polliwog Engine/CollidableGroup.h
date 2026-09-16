#pragma once

#ifndef _CollidableGroup
#define _CollidableGroup

#include "CollisionManager.h"
#include <list>

class CollidableGroupCollection;
class CollisionAABB;
class Collidable;

class CollidableGroup
{
private:
	// Data Structure: List
	using CollidableCollection = std::list<Collidable*>;
	CollidableCollection ColCollection;

	CollisionAABB* theBox; //Collision box used for more effcient collisions
	CollisionAABB* TestBox; //Added for computational purposes

public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator=(const CollidableGroup&) = delete;
	~CollidableGroup();

	using ColCollectionRef = CollidableCollection::iterator;

	void Deregister(const ColCollectionRef& ref);
	const CollidableCollection& GetColliderCollection();
	void Register(Collidable* col, ColCollectionRef& ref);

	void ComputeBox(); //Computing group AABB box

	// Accessor
	CollisionAABB* getBox() const
	{
		return theBox;
	};

};


#endif _CollidableGroup