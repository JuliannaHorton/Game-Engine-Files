#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "CollisionTestCommand.h"

int CollisionManager::TypeIDNextNumber = 0;

CollisionManager::CollisionManager()
{
	ColGroupCollection.resize(MAX_COLLISION_GROUP);
}

void CollisionManager::SetGroupForTypeID(CollisionManager::PWTypeID ind)
{
	if (ColGroupCollection[ind] == nullptr)
		ColGroupCollection[ind] = new CollidableGroup();
}

// Clean-Up
CollisionManager::~CollisionManager()
{
	for (const auto Col : ColGroupCollection)
	{
		delete Col;
	}

	for (const auto ColTest : colTestCommands)
	{
		delete ColTest;
	}

	ColGroupCollection.clear();
	colTestCommands.clear();
}

void CollisionManager::ProcessCollisions()
{
	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->execute();
	}
}

