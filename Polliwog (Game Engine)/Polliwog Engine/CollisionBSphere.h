#pragma once

#ifndef _CollisionBSphere
#define _CollisionBSphere

#include "CollisionVolume.h"

class CollisionAABB;
class Model;

class CollisionBSphere : public CollisionVolume
{
public:
	CollisionBSphere() = default;
	CollisionBSphere(const CollisionBSphere&) = delete;
	CollisionBSphere& operator=(const CollisionBSphere&) = delete;
	~CollisionBSphere() = default;

	//Accessors 
	const Matrix& GetWorld() const;
	const Vect& GetCenter() const;
	const float GetRadius() const;

	virtual void ComputeData(const Model* mod, const Matrix& mat);
	virtual void DebugView(const Vect& col) const;

	virtual bool IntersectAccept(const CollisionVolume& other) const;
	virtual bool IntersectVisit(const CollisionBSphere& other) const;
	virtual bool IntersectVisit(const CollisionBox& other) const;

private:

	Matrix World = Matrix(IDENTITY);

	Vect Center = Vect(0,0,0);
	float Radius = 0;
};

#endif _CollisionBSphere