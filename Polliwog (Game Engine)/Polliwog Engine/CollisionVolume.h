#pragma once

#ifndef _CollisionVolume
#define _CollisionVolume

#include "../Polliwog Engine/GameObject.h"

class CollisionBSphere;
class CollisionBox;
class CollisionAABB;
class CollisionOBB;
class Model;

class CollisionVolume
{
public:

	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator=(const CollisionVolume&) = delete;
	virtual ~CollisionVolume() = default;

	virtual void ComputeData(const Model* mod, const Matrix& mat) = 0;
	virtual void DebugView(const Vect& col) const = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionBox& other) const = 0;


};

#endif _CollisionVolume