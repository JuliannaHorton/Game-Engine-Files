#pragma once

#ifndef _Collidable
#define _Collidable

#include "CollisionManager.h"
#include "CollidableGroup.h"
#include "RegistrationState.h"
#include "SceneAttorney.h"

class CollisionRegistrationCmd;
class CollisionDeregistrationCmd;

//#include "CollisionBSphere.h"

class CollisionBSphere;
class CollisionVolume;
class Model;

class Collidable
{
	friend class CollisionAttorney;

public:
	Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;
	virtual ~Collidable();

	//Enum used for user volume selection
	enum class Volume_Type
	{
		BSphere,
		AABB,
		OBB
	};

	using PWTypeID = int;
	static const PWTypeID PWID_UNDEFINED = -1;

	//
	// User Registration and Deregistration methods
	//
	void SubmitCollisionDeregistration();
	void SubmitCollisionRegistration();

	void setDelete(const CollidableGroup::ColCollectionRef& ref);

	//
	// Accessors
	//
	const CollisionVolume& GetCollisionVolume();
	const CollisionBSphere& GetDefaultBSphere();

	void SetColliderModel(Model* mod, Volume_Type vt); //Game Objects Model and User chosen Volume type
	void UpdateCollsionData(const Matrix& mat); //Game Objects Position


private:

	Model* pColModel;
	Matrix World;
	CollisionVolume* pColVolume; //User selected volume
	CollisionBSphere* pTestSphere; //BSphere used for effcient collision testing

	CollisionManager::PWTypeID myID = CollisionManager::PWID_UNDEFINED;

	CollidableGroup::ColCollectionRef pMyDeleteRef; //Delete Reference
	RegistrationState RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
	CollisionRegistrationCmd* pRegistrationCmd;
	CollisionDeregistrationCmd* pDeregistrationCmd;

	//Accessable via attorney
	void SceneDeregistration();
	void SceneRegistration();


protected:
	// Each Collidable will be added to a Collision group in order to be tested as either a pair or self
	template < typename C > //STL FUN!!!
	void SetCollidableGroup()
	{
		myID = SceneAttorney::Xables::getCollisionMgr(SceneManager::getCurrentScene())->GetTypeID<C>(); //I probably don't need to reference the actual scene in this way
	}

};

#endif _Collidable