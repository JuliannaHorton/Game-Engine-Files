#include "Collidable.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeregistrationCommand.h"
#include "SceneManager.h"

#include "CollisionBox.h"
#include "CollisionBSphere.h"
#include "CollisionAABB.h"
#include "CollisionOBB.h"
#include "CollisionVolume.h"

Collidable::Collidable()
{
	pColVolume = nullptr; // CollidableVolume set by the User in SetColliderModel
	pTestSphere = nullptr; // BSphere for testing collision
	pColModel = nullptr; //Collidable objects model, also set by the User in SetColliderModel

	// Collision Registration commands
	// Storing Commands here to prevent unneeded duplication
	pRegistrationCmd = new CollisionRegistrationCmd(this);
	pDeregistrationCmd = new CollisionDeregistrationCmd(this);
}


Collidable::~Collidable()
{
	delete pRegistrationCmd;
	delete pDeregistrationCmd;
	delete pTestSphere;

	if (pColVolume != nullptr)
		delete pColVolume;
}



//Registration and Deregistration
	/// <summary>
	/// \brief Registers a Game Object as Collidable
	/// \ingroup COLLISIONCONTROL
	///
	/// In order for a Game Object to Collide with other objects the user must register it and Set it Collision Group.
	/// <br>
	/// <br>
	/// First in the Scene Set the Collision Pair or Self:
	/// <br>
	/// \code 
	/// <...>
	/// void TankScene::Intialize()
	/// {
	/// <...>
	///     SetCollisionPair<Tank, Bullet>(); //Sets Collision between two selected classes created by the user
	///		SetCollisionSelf<Tank>(); //Sets Collision between entities of the same class
	/// <...>
	///  }
	/// \endcode
	/// Once its Collision type is set in Scene the user must set it as a group and register it as Collidable
	/// \code
	/// Tank::Tank()
	/// {
	/// <...>
	/// 	SetCollidableGroup<Tank>();
	///     Collidable::SubmitCollisionRegistration();
	/// <...>
	/// }
	/// \endcode
	/// In Update be sure to Update the Game Objects current Position
	/// 
	/// \note If the object is not supposed to move (as in it has no Update), put this in the constructor. 
	///       As long as the Collision data knows where the object is this will work fine.
	/// 
	/// 
	/// \code
	/// Tank::Update()
	/// {
	///		UpdateCollsionData(World);
	/// }
	/// \endcode
	/// Now the Tank class can use Collide(GameObject*) methods based on the Pairs/Self set in the Scene
	/// \code
	/// {
	/// <...>
	///		void Tank::Collision(Bullet*) { print("Collision between Tank and Bullet"); };
	///		void Tank::Collision(Tank*) { print("Collision between Tank and Tank"); };
	/// <...>
	/// }
	/// \endcode
	/// <...>
	/// 
	/// </summary>
void Collidable::SubmitCollisionRegistration()
{
	assert(RegStateCurr == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pRegistrationCmd);

	RegStateCurr = RegistrationState::PENDING_REGISTRATION;
}

void Collidable::SubmitCollisionDeregistration()
{
	if (RegStateCurr == RegistrationState::CURRENTLY_REGISTERED)
	{
		//assert(RegData[idNum].RegStateCurr == RegistrationState::CURRENTLY_REGISTERED);
		SceneAttorney::Xables::SubmitCommand(SceneManager::getCurrentScene(), pDeregistrationCmd);

		RegStateCurr = RegistrationState::PENDING_DEREGISTRATION;
	}
}

void Collidable::SceneRegistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::Xables::getCollisionMgr(SceneManager::getCurrentScene())->GetColGroup(myID)[myID]->Register(this, pMyDeleteRef); //[myId]??

	RegStateCurr = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDeregistration()
{
	assert(RegStateCurr == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::Xables::getCollisionMgr(SceneManager::getCurrentScene())->GetColGroup(myID)[myID]->Deregister(pMyDeleteRef); //[myId]??

	RegStateCurr = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::setDelete(const CollidableGroup::ColCollectionRef& ref)
{
	pMyDeleteRef = ref; //Save the reference, so we don't need to hunt it down
}



/// <summary>
/// \brief Sets the Collision Model 
/// \ingroup COLLISIONCONTROL
/// 
/// The user gets to choose between 3 different types of collision models:
/// <br>AABB box, OBB box, or a BSphere
/// 
/// </summary>
void Collidable::SetColliderModel(Model* mod, Volume_Type vt) //The GameObject's Model
{
	assert(mod != nullptr);

	pTestSphere = new CollisionBSphere();
	pColModel = mod;

	//Hmm, this could be better
	if (vt == Volume_Type::BSphere)
	{
		pColVolume = new CollisionBSphere();
	}
	else if (vt == Volume_Type::AABB)
	{
		pColVolume = new CollisionAABB();
	}
	else if (vt == Volume_Type::OBB)
	{
		pColVolume = new CollisionOBB();
	}
	else
	{
		pColVolume = new CollisionAABB();
	}
}

/// <summary>
/// \brief Allows you to get the CollisionVolume that the user selected
/// \ingroup COLLISIONCONTROL
/// 
/// </summary>
const CollisionVolume& Collidable::GetCollisionVolume()
{
	return *pColVolume;
}

/// <summary>
/// \brief Allows you to get the CollisionBSphere that's used for efficient collision testing
/// \ingroup COLLISIONCONTROL
/// 
/// </summary>
const CollisionBSphere& Collidable::GetDefaultBSphere()
{
	return *pTestSphere;
}

/// <summary>
/// \brief Used by the user to update their collision data
/// \ingroup COLLISIONCONTROL
///
/// Every time the Game Object moves this should be called 
/// <br>
/// <br>
/// This can be done inside a constructor or Update()
/// <br>
/// \code 
/// <...>
/// void Tank::Tank()
/// {
/// <...>
///		SetColliderModel(myTank->getModel(), Collidable::Volume_Type::OBB);
///		SetCollidableGroup<Tank>();
///		Collidable::SubmitCollisionRegistration();
/// 
///     UpdateCollsionData(World); //Update the collidable
/// <...>
///  }
/// void Tank::Update()
/// {
/// <...>
///		//The Tank moves
/// 	if (Keyboard::GetKeyboardState(FROG_KEY::KEY_A))
///		{
///			TankRotTrans = Matrix(ROT_Y, TankRotAng) * TankRotTrans;
///		}
/// 
///		//Therefore we need to update the data
///     UpdateCollsionData(World);
/// <...>
///  }
/// \endcode
/// </summary>
void Collidable::UpdateCollsionData(const Matrix& mat) //The GameObject's Position
{
	assert(pColModel != nullptr && "No model set, Please be sure to SetColliderModel before updating any data");

	World = mat;

	pTestSphere->ComputeData(pColModel, mat);
	pColVolume->ComputeData(pColModel, mat);

}