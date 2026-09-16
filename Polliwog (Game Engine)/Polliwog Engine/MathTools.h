#pragma once

#ifndef _MathTools
#define _MathTools

#include "Vect.h"

class CollisionVolume;
class CollisionBSphere;
class CollisionAABB;
class CollisionOBB;
class CollisionBox;


class MathTools
{
public:

	static bool Intersect(const CollisionVolume& A, const CollisionVolume& B); //UHHHHGGGGGG I need to find my math notebook
	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether two Spheres are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionBSphere& A, const CollisionBSphere& B); //UHHHHGGGGGG I need to find my math notebook

	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether two AABBs are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionAABB& A, const CollisionAABB& B);
	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether an AABB and BSphere are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionAABB& A, const CollisionBSphere& B);
	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether an AABB and BSphere are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionOBB& A, const CollisionOBB& B);
	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether an AABB and BSphere are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionOBB& A, const CollisionAABB& B);
	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether an AABB and BSphere are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionOBB& A, const CollisionBSphere& B);
	/// <summary>
	/// \ingroup MATH
	// \brief Checks whether an AABB and BSphere are intersecting
	/// </summary>
	/// <param name="name"></param>
	static bool Intersect(const CollisionVolume& A, const CollisionBox& B);

	//static bool Intersect(const CollisionAABB& A, const CollisionAABB& B);


	/// <summary>
	/// \ingroup MATH
	/// \brief Returns a restricted value within the specified minimum and maximum.
	/// 
	/// </summary>
	/// <param name="name"></param>
	static float Clamp(float min, float max, float intersect); //Acts as mainly a support method


	/// <summary>
	/// \ingroup MATH
	/// \brief Performs SATTest for OBB collisions
	/// 
	/// </summary>
	/// <param name="name"></param>
	static bool MathTools::SATtest(const Vect& testV, const CollisionOBB& A, const CollisionOBB& B); //Acts as mainly a support method

	/// <summary>
	/// \ingroup MATH
	/// \brief Performs SATTest for OBB collisions
	/// 
	/// </summary>
	/// <param name="name"></param>
	static bool MathTools::SATtest(const Vect& testV, const CollisionOBB& A, const CollisionAABB& B);//Acts as mainly a support method

	/// <summary>
	/// \ingroup MATH
	/// \brief Returns maximum scalar projection
	/// 
	/// </summary>
	/// <param name="name"></param>
	static float MathTools::ProjMax(const Vect& VectInv, const float scale, const float len, const Vect& MaxV);

	/// <summary>
	/// \ingroup MATH
	/// \brief Returns a 2D object's position in 3D space.
	/// 
	/// This 2D object could be a sprite or mouse pointer. Knowing their 3D position could allow for specific in-game functions
	/// \n
	/// \n
	/// For Example:
	/// \n \t
	/// Here I want my Tank's gun to follow my mouse pointer
	/// \code
	/// //...
	/// //I chose to send the mouse position directly to my tank's head and have it saved as 'MousePos'
	/// Vect MousePos = MathTools::ScreentoGame(Mx, My);
	/// TankHead->SendMouse(MousePos); //IT FINALLY WORKS
	/// //...
	/// void TankHead::Update(Matrix body)
	///{
	///		Vect test = MousePos - body.get(ROW_3);
	///
	///		Vect localDir = test * body.getInv();  //Convert to local space
	///		test.norm();  // normalize direction
	///
	///		//Get the radian rotation for Y-Axis (yaw) and X-Axis (pitch) 
	///		float yaw = atan2(localDir.X(), localDir.Z());
	///		float pitch = atan2(localDir.Y(), localDir.Z());
	///		
	///		\\Create new Translations
	///		WorldHead = TankHeadScale * Matrix(ROT_Y, yaw) * body;
	///		TankHeadRotTrans = Matrix(ROT_Y, yaw);
	///		myTankHead->SetWorld(WorldHead);
	///
	///		WorldGun = TankGunScale * Matrix(TRANS, 0, 14, 7) * Matrix(ROT_X, pitch) * Matrix(ROT_Y, yaw) * body;
	///		TankGunRotTrans = Matrix(TRANS, 0, 14, 7) * Matrix(ROT_X, pitch);
	///		myTankGun->SetWorld(WorldGun);
	///}
	/// \endcode
	/// </summary>
	/// <param name="name"></param>
	static Vect ScreentoGame(const float x, const float y);


	//Note to Self: Add math stuff for moving an object forward and rotation so the User doesn't need to worry about translation matrices
};

#endif _MathTools