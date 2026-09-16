#pragma once

#ifndef _CollisionAABB
#define _CollisionAABB

#include "CollisionBox.h"

class CollisionBSphere;

class CollisionAABB : public CollisionBox
{
public:
	CollisionAABB() = default;
	CollisionAABB(const CollisionAABB&) = default;
	CollisionAABB& operator=(const CollisionAABB&) = default;
	~CollisionAABB() = default;

	//Accessors
	const Vect& GetMin() const;
	const Vect& GetMax() const;

	void SetMin(const Vect& min) { CornerMin = min; };
	void SetMax(const Vect& max) { CornerMax = max; };

	virtual void ComputeData(const Model* mod, const Matrix& mat);
	virtual void ComputeData(const CollisionBSphere& sphere);
	virtual void ComputeData(const Vect& Min, const Vect& Max);
	virtual void CombineValues(const CollisionAABB& secondAABB);
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

#endif _CollisionAABB