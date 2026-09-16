#include "CollisionOBB.h"
#include "VisualAttorney.h"
#include "MathTools.h"
#include "CollisionBox.h"

//Get Info
const Vect& CollisionOBB::GetMax() const
{
	return CornerMax;
}

const Vect& CollisionOBB::GetMin() const
{
	return CornerMin;
}


//Data
void CollisionOBB::ComputeData(const Model* mod, const Matrix& mat)
{
	ModelWorld = mat;

	CornerMin = mod->getMinAABB();
	CornerMax = mod->getMaxAABB();

	halfD = (CornerMax - CornerMin) * 0.5f;
	Center = ((CornerMax + CornerMin) * 0.5f) * ModelWorld;
	// UpVector * UpVector
	ScaleFact = ModelWorld.get(ROW_1).dot(ModelWorld.get(ROW_1));
}

void CollisionOBB::ComputeData(const Vect max, const Vect min, const Matrix& mat)
{
	ModelWorld = mat;

	CornerMin = max;
	CornerMax = min;

	halfD = (CornerMax - CornerMin) * 0.5f;
	Center = ((CornerMax + CornerMin) * 0.5f) * ModelWorld;
	// UpVector * UpVector
	ScaleFact = ModelWorld.get(ROW_1).dot(ModelWorld.get(ROW_1));
}


void CollisionOBB::DebugView(const Vect& col) const
{
	VisualAttorney::Box::ShowOBB(*this, col);
}

bool CollisionOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionOBB::IntersectVisit(const CollisionBox& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionOBB::IntersectVisit(const CollisionBSphere& other) const
{
	return MathTools::Intersect(*this, other);
}

bool CollisionOBB::IntersectVisit(const CollisionAABB& other) const
{
	return MathTools::Intersect(*this, other);
}

bool CollisionOBB::IntersectVisit(const CollisionOBB& other) const
{
	return MathTools::Intersect(*this, other);
}

