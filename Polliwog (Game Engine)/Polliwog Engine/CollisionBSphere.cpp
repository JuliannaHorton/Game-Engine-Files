#include "CollisionBSphere.h"
#include "CollisionBox.h"
#include "CollisionOBB.h"
#include "CollisionAABB.h"
#include "VisualAttorney.h"
#include "MathTools.h"

//Get Info
const float CollisionBSphere::GetRadius() const
{
	return Radius;
}

const Vect& CollisionBSphere::GetCenter() const
{
	return Center;
}

const Matrix& CollisionBSphere::GetWorld() const
{
	return World;
}

//Data
void CollisionBSphere::ComputeData(const Model* mod, const Matrix& mat)
{
	World = mat;
	Center = mod->getCenter() * mat;

	float modelRadius = mod->getRadius();

	// Find the magnitude along the X variables of the matrix, to get the X scale
	float scaleX = Vect(mat.M0(), mat.M4(), mat.M8()).mag();

	Radius = modelRadius * scaleX;
}


void CollisionBSphere::DebugView(const Vect& col) const
{
	VisualAttorney::Sphere::ShowBSphere(*this, col);
}


bool CollisionBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionBSphere::IntersectVisit(const CollisionBox& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionBSphere::IntersectVisit(const CollisionBSphere& other) const
{
	return MathTools::Intersect(*this, other);
}