#pragma once

#ifndef _TRAIterator
#define _TRAIterator

#include "Terrain.h"
#include "CollisionAABB.h"
#include <iostream>

class TerrainRectangleArea;
class CollisionAABB;

class TRAIterator
{

private:

	TerrainRectangleArea& pArea;
	Cell itCell;
	std::pair<int, int> current;

public:
	TRAIterator() = default;
	TRAIterator(const TRAIterator&) = default;
	TRAIterator& operator=(const TRAIterator&) = delete;
	~TRAIterator() = default;

	TRAIterator(std::pair<int, int> cel, TerrainRectangleArea* );

	TRAIterator& operator++();
	bool operator!=(const TRAIterator& other) const;

	CollisionAABB* getCellAABB();
};

#endif _TRAIterator