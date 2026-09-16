#pragma once

#ifndef _Terrain
#define _Terrain

#include "../PollywogBog.h"

#include "Vect.h"
struct VertexStride_VUN;
struct TriangleIndex;

#include <iostream>
#include <vector>
#include "Drawable.h"

class GameObject;
class CollisionAABB;

// I know it isn't minimal, but we need the Norms, Max, and Min... but I found the inclusion of the original points helpful
struct Cell
{
	Vect Min;
	Vect Max;

	Vect tRNorm;
	Vect tLNorm;
	Vect bRNorm;
	Vect bLNorm;

	//I could ellminate these by calculating them with the min and max
	Vect tR;
	Vect tL;
	Vect bR;
	Vect bL;
};

class Terrain : public Drawable
{

public:
	Terrain() = default;
	Terrain(const Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;
	~Terrain();

	Terrain(Texture* heightMap, Texture* texture, int U = 1, int V = 1, float length = 100, float maxHeight = 10, float yValue = 0);

	virtual void Draw(); //Its a drawable --- Gasp!

	//Accessors

	Model* GetModel() { return pModTerrain; };
	const std::pair<int, int> GetCellBelow(const Vect& pos);
	float GetHeight(const Vect& height);
	const Vect& GetNormal(const Vect& normal);
	const Cell& GetCell(int x, int y);


	CollisionAABB* returnBox() { return testBox; }; //Just needed a place to store a consistent box to test collision with

private:

	std::vector<std::vector<Cell>> CellList;  //Data Structure

	GraphicObject_TextureLight* TerrainTest;
	CollisionAABB* testBox;

	// Basic Appearance
	Model* pModTerrain;
	Texture* myMap;
	Texture* myTex;
	Vect myColor;

	//Values used to calculate Terrain
	int u;
	int v;
	int sideLength;
	int maxHeight;
	float yValue;

	float size;
	int SideNum; 

	// Other
	StandardVertex* pVerts;
	TriangleByIndex* pTriList;

	//Visualize tools and methods just used in Terrain
	void visualizeCellBelow(Vect pos); //Visualizes the original Points
	void visualizeWireFramePoints(Vect pos); //Visualizes the Min and Max Points
	int TexelIndex(int side, int row, int col) const;



};

#endif _ShaderManager