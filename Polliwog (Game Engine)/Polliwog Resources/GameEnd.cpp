
#include "../Finalsprint/Polliwog Engine/Tadpole.h"
#include "../User Defined Code/BulletFactory.h"
#include "../User Defined Code/EnemyBulletFactory.h"
#include "../User Defined Code/LittleGuyFactory.h"
#include "../User Defined Code/HUDAccess.h"
#include "../User Defined Code/LevelEventManager.h"

/// <summary>
/// \brief Cleans up code after the game has ended
/// \ingroup FEATURES
/// 
/// For Example: I used it here to clean up my bullet factor
/// \code
/// void Polliwog::GameEnd() //User Defined
///{
///	BulletFactory::Terminate();
///	EnemyBulletFactory::Terminate();
///}
/// \endcode
/// </summary>
void Tadpole::GameEnd() //User Defined
{
	BulletFactory::Terminate();
	EnemyBulletFactory::Terminate();
	LittleGuyFactory::Terminate();
	LevelEventManager::Terminate();
}