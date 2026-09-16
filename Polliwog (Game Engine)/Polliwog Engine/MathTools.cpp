#include "MathTools.h"
#include "Tadpole.h"
#include "Scene.h"
#include "CollisionBSphere.h"
#include "CollisionAABB.h"
#include "CollisionOBB.h"

//Visitor Pattern
bool MathTools::Intersect(const CollisionVolume& A, const CollisionVolume& B)
{
	return A.IntersectAccept(B);
}

bool MathTools::Intersect(const CollisionVolume& A, const CollisionBox& B)
{
	return B.IntersectAccept(A);
}

// BSphere v BSphere
bool MathTools::Intersect(const CollisionBSphere& A, const CollisionBSphere& B)
{
	//The Distance between the two BSpheres, Magnitude(CenterA - CenterB)
	const Vect& ColCenter = A.GetCenter() - B.GetCenter();
	float C = ColCenter.dot(ColCenter);

	//Size of the two BSphere's radius
	float Sum = A.GetRadius() + B.GetRadius();
	float R = (Sum * Sum);


	//If the Distance is smaller than the two Radiuses, then the two BSpheres overlap
	return C < R;
}

// AABB Bounding Box v AABB Bounding Box
bool MathTools::Intersect(const CollisionAABB& A, const CollisionAABB& B)
{
	// Grabbing all the Min and Max
	const Vect& MinA = A.GetMin();
	const Vect& MaxA = A.GetMax();
	const Vect& MinB = B.GetMin();
	const Vect& MaxB = B.GetMax();

	//Check for overlap in all 3 axes
	return (MinA.X() <= MaxB.X() && MaxA.X() >= MinB.X()
		&& MinA.Y() <= MaxB.Y() && MaxA.Y() >= MinB.Y()
		&& MinA.Z() <= MaxB.Z() && MaxA.Z() >= MinB.Z());
}

//  OBB Bounding Box v OBB Bounding Box
bool MathTools::Intersect(const CollisionOBB& A, const CollisionOBB& B)
{
	// Get World Matrix
	const Matrix& WorldA = A.GetMatrix();
	const Matrix& WorldB = B.GetMatrix();

	// Axes on both objects
	return (SATtest(WorldA.get(ROW_0), A, B) && SATtest(WorldA.get(ROW_1), A, B) && SATtest(WorldA.get(ROW_2), A, B) &&
		SATtest(WorldB.get(ROW_0), A, B) && SATtest(WorldB.get(ROW_1), A, B) && SATtest(WorldB.get(ROW_2), A, B) &&
		SATtest(WorldA.get(ROW_0).cross(WorldB.get(ROW_0)), A, B) && SATtest(WorldA.get(ROW_1).cross(WorldB.get(ROW_1)), A, B) &&
		SATtest(WorldA.get(ROW_1).cross(WorldB.get(ROW_2)), A, B) && SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_0)), A, B) &&
		SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_0)), A, B) && SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_1)), A, B) &&
		SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_2)), A, B));
}

//  AABB Bounding Box v BSphere
bool MathTools::Intersect(const CollisionAABB& A, const CollisionBSphere& B)
{
	//Grabbing needed values
	const Vect& MinA = A.GetMin();
	const Vect& MaxA = A.GetMax();

	const Vect& Center = B.GetCenter();

	//Clamping
	Vect Clamped;
	Clamped.X() = Clamp(MinA.X(), MaxA.X(), Center.X());
	Clamped.Y() = Clamp(MinA.Y(), MaxA.Y(), Center.Y());
	Clamped.Z() = Clamp(MinA.Z(), MaxA.Z(), Center.Z());

	Vect C = Clamped - Center;
	float R = B.GetRadius() * B.GetRadius();

	// C.Magnitude() < B.Radius()
	return (C.dot(C) < R);
}

// OBB Bounding Box v BSphere
bool MathTools::Intersect(const CollisionOBB& A, const CollisionBSphere& B)
{
	//Get needed values
	const Matrix& World = A.GetMatrix();
	const Vect& MinA = A.GetMin();
	const Vect& MaxA = A.GetMax();

	const Vect& Center = B.GetCenter();

	// Transform the sphere center into the OBB's local space
	Vect C = Center * World.getInv();

	// Find the closest point on the OBB to the sphere center in local space
	Vect Clamped;
	Clamped.X() = Clamp(MinA.X(), MaxA.X(), C.X());
	Clamped.Y() = Clamp(MinA.Y(), MaxA.Y(), C.Y());
	Clamped.Z() = Clamp(MinA.Z(), MaxA.Z(), C.Z());

	Vect Q = Clamped * World;

	Vect test = Q - Center;

	float R = B.GetRadius() * B.GetRadius();

	// If squared distance is less than squared radius, they intersect
	return (test.dot(test) < R);
}

// OBB Bounding Box v AABB Bounding Box
bool MathTools::Intersect(const CollisionOBB& A, const CollisionAABB& B)
{
	const Matrix& WorldA = A.GetMatrix();

	// AABB is already axes aligned
	const Matrix& WorldB = B.GetMatrix();

	// Axes on both objects
	return (SATtest(WorldA.get(ROW_0), A, B) && SATtest(WorldA.get(ROW_1), A, B) && SATtest(WorldA.get(ROW_2), A, B) &&
		SATtest(WorldB.get(ROW_0), A, B) && SATtest(WorldB.get(ROW_1), A, B) && SATtest(WorldB.get(ROW_2), A, B) &&
		SATtest(WorldA.get(ROW_0).cross(WorldB.get(ROW_0)), A, B) && SATtest(WorldA.get(ROW_1).cross(WorldB.get(ROW_1)), A, B) &&
		SATtest(WorldA.get(ROW_1).cross(WorldB.get(ROW_2)), A, B) && SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_0)), A, B) &&
		SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_0)), A, B) && SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_1)), A, B) &&
		SATtest(WorldA.get(ROW_2).cross(WorldB.get(ROW_2)), A, B));
}

bool MathTools::SATtest(const Vect& testV, const CollisionOBB& A, const CollisionOBB& B)
{
	// Checks if vector is (0, 0, 0)
	if (!(testV.magSqr() > FLT_EPSILON))
		return true;

	//Use the values for fun GAM 325 magic
	float magV = testV.mag();
	float ProjMaxA = ProjMax((testV * A.GetMatrix().getInv()), A.GetScaleFactor(), magV, A.GetHalfDiagonal());

	float ProjMaxB = ProjMax((testV * B.GetMatrix().getInv()), B.GetScaleFactor(), magV, B.GetHalfDiagonal());

	float D = abs((A.GetCenter() - B.GetCenter()).dot(testV)) / magV;

	return D <= (ProjMaxA + ProjMaxB);
}

bool MathTools::SATtest(const Vect& testV, const CollisionOBB& A, const CollisionAABB& B) //A second one for AABB
{
	// Checks if vector is (0, 0, 0)
	if (!(testV.magSqr() > FLT_EPSILON))
		return true;

	//Use the values for fun GAM 325 magic
	float magV = testV.mag();
	float ProjMaxA = ProjMax((testV * A.GetMatrix().getInv()), A.GetScaleFactor(), magV, A.GetHalfDiagonal());

	float ProjMaxB = ProjMax((testV * B.GetMatrix().getInv()), B.GetScaleFactor(), magV, B.GetHalfDiagonal());

	float D = abs((A.GetCenter() - B.GetCenter()).dot(testV)) / magV;

	return D <= (ProjMaxA + ProjMaxB);
}

float MathTools::ProjMax(const Vect& VectInv, const float scale, const float len, const Vect& MaxV)
{
	float Ax = abs(VectInv.X() * MaxV.X());
	float By = abs(VectInv.Y() * MaxV.Y());
	float Cz = abs(VectInv.Z() * MaxV.Z());

	float iMax = (Ax + By + Cz) / len;

	return (scale * iMax);
}



float MathTools::Clamp(float min, float max, float intersect)
{
	if (intersect < min)
		return min;
	else if (max < intersect)
		return max;
	else
		return intersect;
}


Vect MathTools::ScreentoGame(float x, float y) //I hated doing this
{
	float NDCx = (2.0f * x / (float)Tadpole::GetWidth()) - 1.0f;
	float NDCy = 1.0f - (2.0f * y / (float)Tadpole::GetHeight());

	Vect ScreenPos = Vect(NDCx, NDCy, 1.0f, 1.0f);

	Matrix Persp;
	Persp = SceneManager::getCurrentScene()->getCamera()->getProjMatrix();
	Matrix View;
	View = SceneManager::getCurrentScene()->getCamera()->getViewMatrix();

	Matrix in = (View * Persp); //I was multiplying Persp * View... *face slap*
	in.inv();

	Vect worldPos = ScreenPos * in;
	float invW = 1.0f / worldPos.W();
	worldPos.X() *= invW;
	worldPos.Y() *= invW;
	worldPos.Z() *= invW;

	return worldPos;
}