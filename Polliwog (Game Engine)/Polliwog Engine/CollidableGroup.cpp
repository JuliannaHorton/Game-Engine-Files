#include "CollidableGroup.h"
#include "CollisionAABB.h"
#include "Collidable.h"

CollidableGroup::CollidableGroup()
{
	theBox = new CollisionAABB();
	TestBox = new CollisionAABB();
}

void CollidableGroup::ComputeBox()
{
	//Compute first box
	auto Col = ColCollection.begin();
	const CollisionBSphere& Sphere1 = (*Col)->GetDefaultBSphere();

	theBox->ComputeData(Sphere1);

	// Add each consecutive box in the list
	++Col;
	while (Col != ColCollection.end())
	{
		TestBox->ComputeData((*Col)->GetDefaultBSphere()); //Compute data for one box

		theBox->CombineValues(*TestBox); // Combine into the whole box

		++Col;
	}
}

void CollidableGroup::Register(Collidable* col, ColCollectionRef& ref)
{
	ref = ColCollection.insert(ColCollection.end(), col);

	col->setDelete(ref);
}

void CollidableGroup::Deregister(const ColCollectionRef& ref)
{
	ColCollection.erase(ref);
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection() //Why do I need to do CollidableGroup
{
	return ColCollection;
}

CollidableGroup::~CollidableGroup()
{
	delete theBox;
	delete TestBox;

	ColCollection.clear();
}