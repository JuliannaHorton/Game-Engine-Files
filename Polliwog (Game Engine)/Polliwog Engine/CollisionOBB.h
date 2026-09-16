#pragma once

#ifndef _CollisionOBB
#define _CollisionOBB

#include "CollisionBox.h"

class CollisionOBB : public CollisionBox
{
public:
	CollisionOBB() = default;
	CollisionOBB(const CollisionOBB&) = delete;
	CollisionOBB& operator=(const CollisionOBB&) = delete;
	~CollisionOBB() = default;

	//Accessors
	const Vect& GetMin() const;
	const Vect& GetMax() const;

	virtual void ComputeData(const Model* mod, const Matrix& mat);
	virtual void ComputeData(const Vect max, const Vect min, const Matrix& mat);
	virtual void DebugView(const Vect& col) const;

	virtual bool IntersectAccept(const CollisionVolume& other) const;
	virtual bool IntersectVisit(const CollisionBox& other) const;
	virtual bool IntersectVisit(const CollisionBSphere& other) const;
	virtual bool IntersectVisit(const CollisionAABB& other) const;
	virtual bool IntersectVisit(const CollisionOBB& other) const;


private:
	Vect CornerMax = Vect(0,0,0);
	Vect CornerMin = Vect(0,0,0);

};

#endif _CollisionOBB