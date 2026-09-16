#pragma once

#ifndef _TerrainRectangleArea
#define _TerrainRectangleArea

#include <iostream>
#include "Terrain.h"

class Collidable;
class CollisionAABB;
class TRAIterator;

class TerrainRectangleArea
{

public:
	TerrainRectangleArea() = default;
	TerrainRectangleArea(const TerrainRectangleArea&) = default;
	TerrainRectangleArea& operator=(const TerrainRectangleArea&) = delete;
	~TerrainRectangleArea() = default;

	TerrainRectangleArea(Collidable* Col);

	Cell Next(int, int);
	CollisionAABB* getTerrBox();

	TRAIterator Begin();
	TRAIterator End();

private:

	Terrain* pTerrain;
	std::pair<int, int> start;
	std::pair<int, int> end;

};

#endif _TerrainRectangleArea