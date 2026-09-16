#pragma once

#ifndef _TerrainStrat
#define _TerrainStrat

class Terrain;

class TerrainStrat
{
public:
	TerrainStrat() = default;
	TerrainStrat(const TerrainStrat&) = delete;
	TerrainStrat& operator=(const TerrainStrat&) = delete;
	virtual ~TerrainStrat() = default;

	virtual void DrawTerrain() = 0;

	void setTerrain(Terrain* s) { ptrTerrain = s; };

protected:
	Terrain* ptrTerrain = nullptr;
};

#endif _TerrainStrat