#pragma once

#ifndef _TerrainNull
#define _TerrainNull

#include "TerrainStrat.h"

class TerrainNull : public TerrainStrat
{
public:
	TerrainNull() = default;
	TerrainNull(const TerrainNull&) = delete;
	TerrainNull& operator=(const TerrainNull&) = delete;
	~TerrainNull() = default;

	virtual void DrawTerrain() {};
};

#endif _TerrainNull
