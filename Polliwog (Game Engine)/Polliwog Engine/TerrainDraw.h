#pragma once

#ifndef _TerrainDraw
#define _TerrainDraw

#include "TerrainStrat.h"

class TerrainDraw : public TerrainStrat
{
public:
	TerrainDraw() = default;
	TerrainDraw(const TerrainDraw&) = delete;
	TerrainDraw& operator=(const TerrainDraw&) = delete;
	~TerrainDraw() = default;

	virtual void DrawTerrain();
};

#endif _TerrainDraw