#pragma once

#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase

class Collidable;

class CollisionDispatchBase
{
public:
	CollisionDispatchBase() = default;
	CollisionDispatchBase(const CollisionDispatchBase&) = delete;
	CollisionDispatchBase& operator=(const CollisionDispatchBase&) = delete;
	virtual ~CollisionDispatchBase() = default;

	virtual void ProcessCallbacks(Collidable* c1, Collidable* c2) = 0;
};

#endif _CollisionDispatchBase