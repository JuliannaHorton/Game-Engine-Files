#pragma once

#ifndef _CollisionManager
#define _CollisionManager

#include "CollisionPairCommand.h"
#include "CollisionSelfCommand.h"
#include "CollisionTerrainCommand.h"
#include "CollisionDispatch.h"

#include <vector>
#include <list>

class Collidable;
class CollidableGroup;
class CollisionTestCmd;

class CollisionManager
{
public:

	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
	~CollisionManager();

	using PWTypeID = int;
	static const PWTypeID PWID_UNDEFINED = -1;

	void ProcessCollisions(); //Shouldn't this have an atterney... 

private:
	const int MAX_COLLISION_GROUP = 20;

	static PWTypeID TypeIDNextNumber;

	//
	// A collection of Collidable GameObject that will be tested 
	// 
	// Data Structure: Vector

	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection ColGroupCollection;

	void SetGroupForTypeID(CollisionManager::PWTypeID ind);

	//
	// A collection of Commands that will be executed within the command center on each registered collidable
	// 
	// Data Structure: List

	using CollisionTestCommands = std::list<CollisionTestCmd*>;
	CollisionTestCommands colTestCommands;


public:
	//
	// STL work
	//
	template <typename C> //Change name later after you understand 

	PWTypeID GetTypeID()
	{
		static PWTypeID myTypeID = TypeIDNextNumber++;
		//CollideGroup stuff (stuff)

		SetGroupForTypeID(myTypeID);

		DebugMsg::out("Type ID: %o\n", myTypeID);
		return myTypeID;
	}

	CollidableGroupCollection GetColGroup(PWTypeID) { return ColGroupCollection; };

	//
	// Creating Collections of Game Objects to test for collision
	//
	template< typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

		CollisionDispatch <C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCommands.push_back(new CollisionPairCmd(pg1, pg2, pDispatch)); //Tests for two collidables of different classes
	}

	template< typename C1>
	void SetCollisionSelf()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];

		CollisionDispatch<C1, C1>* pDispatch = new CollisionDispatch<C1, C1>(); //Self just needs a group of the same object

		colTestCommands.push_back(new CollisionSelfCmd(pg1, pDispatch)); //Tests for every Collidable of the same class 
	}

	template< typename C1>
	void SetCollisionTerrain()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];

		//CollisionTerrainDispatch<C1>* pDispatch = new CollisionTerrainDispatch<C1>(); //Self just needs a group of the same object

		colTestCommands.push_back(new CollisionTerrainCmd(pg1)); //Tests for every Collidable of the same class 
	}

};


#endif _CollisionManager