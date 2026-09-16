#pragma once

#ifndef _CollisionBox
#define _CollisionBox

#include "../Polliwog Engine/CollisionVolume.h"
#include "../Polliwog Engine/CollisionBSphere.h"

class CollisionOBB;
class CollisionAABB;


class CollisionBox : public CollisionVolume
{
public:

	CollisionBox() = default;
	CollisionBox(const CollisionBox&) = default;
	CollisionBox& operator=(const CollisionBox&) = default;
	virtual ~CollisionBox() = default;

	const Matrix& GetMatrix() const { return ModelWorld; }
	const Vect& GetHalfDiagonal() const { return halfD; }
	const Vect& GetCenter() const { return Center; }
	const float GetScaleFactor() const { return ScaleFact; }

	virtual bool IntersectVisit(const CollisionBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionOBB& other) const = 0;

protected:
	Matrix ModelWorld;

	Vect halfD;
	Vect Center;
	float ScaleFact = 0;

};

#endif _CollisionBox