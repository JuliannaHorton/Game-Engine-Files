#include "CollisionAABB.h"
#include "CollisionBox.h"
#include "CollisionBSphere.h"
#include "VisualAttorney.h"
#include "MathTools.h"

//Get Info
const Vect& CollisionAABB::GetMax() const
{
	return CornerMax;
}

const Vect& CollisionAABB::GetMin() const
{
	return CornerMin;
}

// Combining two AABBs
void CollisionAABB::CombineValues(const CollisionAABB& secondAABB)
{
	if (CornerMax.X() < secondAABB.GetMax().X())
		CornerMax.X() = secondAABB.GetMax().X();

	if (CornerMax.Y() < secondAABB.GetMax().Y())
		CornerMax.Y() = secondAABB.GetMax().Y();

	if (CornerMax.Z() < secondAABB.GetMax().Z())
		CornerMax.Z() = secondAABB.GetMax().Z();

	if (CornerMin.X() > secondAABB.GetMin().X())
		CornerMin.X() = secondAABB.GetMin().X();

	if (CornerMin.Y() > secondAABB.GetMin().Y())
		CornerMin.Y() = secondAABB.GetMin().Y();

	if (CornerMin.Z() > secondAABB.GetMin().Z())
		CornerMin.Z() = secondAABB.GetMin().Z();
}

// Added Computing data for default sphere
void CollisionAABB::ComputeData(const CollisionBSphere& sphere)
{
	const Vect& C = sphere.GetCenter();
	const float R = sphere.GetRadius();

	CornerMax = Vect(C.X() + R, C.Y() + R, C.Z() + R);
	CornerMin = Vect(C.X() - R, C.Y() - R, C.Z() - R);

}

//Data
void CollisionAABB::ComputeData(const Model* mod, const Matrix& mat)
{
	//This can be improved... feel ineffecient and too many ifs

	const Vect* box = mod->getVectList();
	int vectNum = mod->getVectNum();

	Vect firstVect = box[0] * mat;
	CornerMin = firstVect;
	CornerMax = firstVect;

	//Loop through each Vect
	for (int x = 1; x < vectNum; x++)
	{
		Vect Curr = box[x] * mat;

		//Check for Min and Max

		// X
		if (Curr.X() > CornerMax.X())
			CornerMax.X() = Curr.X();

		else if (Curr.X() < CornerMin.X())
			CornerMin.X() = Curr.X();

		// Y
		if (Curr.Y() > CornerMax.Y())
			CornerMax.Y() = Curr.Y();

		else if (Curr.Y() < CornerMin.Y())
			CornerMin.Y() = Curr.Y();

		// Z
		if (Curr.Z() > CornerMax.Z())
			CornerMax.Z() = Curr.Z();

		else if (Curr.Z() < CornerMin.Z())
			CornerMin.Z() = Curr.Z();
	}


	ModelWorld = Matrix(IDENTITY); // Matrix doesn't neccissarily matter, but we still need something
	halfD = (CornerMax - CornerMin) * 0.5f;
	Center = ((CornerMax + CornerMin) * 0.5f); // Min and Max are already in World Space

	ScaleFact = 1.0f; // Scale already defined in Min and Max
}

void CollisionAABB::ComputeData(const Vect& Min, const Vect& Max)
{
	//This can be improved... feel ineffecient and too many ifs
	CornerMin = Min;
	CornerMax = Max;


	ModelWorld = Matrix(IDENTITY); // Matrix doesn't neccissarily matter, but we still need something
	halfD = (CornerMax - CornerMin) * 0.5f;
	Center = ((CornerMax + CornerMin) * 0.5f); // Min and Max are already in World Space

	ScaleFact = 1.0f; // Scale already defined in Min and Max
}



void CollisionAABB::DebugView(const Vect& col) const
{
	VisualAttorney::Box::ShowAABB(*this, col);
}

bool CollisionAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionAABB::IntersectVisit(const CollisionBox& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionAABB::IntersectVisit(const CollisionAABB& other) const
{
	return MathTools::Intersect(*this, other);
}

bool CollisionAABB::IntersectVisit(const CollisionBSphere& other) const
{
	return MathTools::Intersect(*this, other);
}

bool CollisionAABB::IntersectVisit(const CollisionOBB& other) const
{
	return MathTools::Intersect(other, *this);
}

