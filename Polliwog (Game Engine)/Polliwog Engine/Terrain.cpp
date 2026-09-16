#include "Terrain.h"
#include "Visualizer.h"
#include "GameObject.h"
#include "CollisionAABB.h"
#include "MathTools.h"
#include "ShaderManager.h"
#include "TextureManager.h"

Terrain::Terrain(Texture* heightMap, Texture* texture, int U, int V, float length, float maxHeight, float yValue)
	: myMap(heightMap), myTex(texture)
{


	//Mostly the same Terrain Code I previously had from 370

	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(L"../Assets/Textures/HMTest.tga", nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	int side = hgtmap->height;

	int height = side - 1;
	int numVerts = side * side;
	int numTri = (height * height * 2);
	SideNum = side - 1;


	pVerts = new StandardVertex[numVerts];
	pTriList = new TriangleByIndex[numTri];

	testBox = new CollisionAABB();

	int vertIndex = 0;
	Vect Min = Vect(0,0,0);
	Vect Max = Vect(0,0,0);

	// Everything except for Min and Max copied and pasted from Graphics
	for (int row = 0; row < side; row++)
	{

		for (int col = 0; col < side; col++)
		{
			uint8_t h_Map = hgtmap->pixels[TexelIndex(side, row, col)]; //Grab the height based on the pixel value

			// I realized my terrain wasn't centered, so I did add "- (length * 0.5f)"... but I don't think that's the problem 
			float x = ((float)col / height) * length - (length * 0.5f);
			float z = ((float)row / height) * length - (length * 0.5f);

			//Wrapping the UVs based on placement and (side-1)
			float u2 = (float)col / height * U;
			float v2 = (float)row / height * V;

			float y = (h_Map / 255.0f) * maxHeight + yValue; //Adjust the height map


			pVerts[vertIndex++].set(x, y, z, u2, v2, 1, 1, 1);
		}
	}

	//Calculate the triangles and face norms
	std::vector<std::vector<Vect>> SumNorm;
	int triIndex = 0;
	CellList.resize(height);
	SumNorm.resize(height);
	for (int row = 0; row < height; row++)
	{
		CellList[row].resize(height);
		SumNorm[row].resize(height);
		for (int col = 0; col < height; col++)
		{
			int topLeft = row * side + col;
			int topRight = row * side + col + 1;
			int bottomLeft = (row + 1) * side + col;
			int bottomRight = (row + 1) * side + col + 1;

			pTriList[triIndex++].set(topLeft, bottomLeft, topRight);
			pTriList[triIndex++].set(topRight, bottomLeft, bottomRight);

			//Triangles
			StandardVertex tL = pVerts[topLeft];
			StandardVertex tR = pVerts[topRight];
			StandardVertex bL = pVerts[bottomLeft];
			StandardVertex bR = pVerts[bottomRight];


			//Everything below is calculating the face normal
			Vect tlV = tL.Pos;
			Vect trV = tR.Pos;
			Vect blV = bL.Pos;
			Vect brV = bR.Pos;

			Vect Norm1 = (trV - tlV).cross(blV - tlV);
			Vect Norm2 = (blV - brV).cross(trV - brV);

			SumNorm[row][col] = (Norm1 + Norm2).norm();
			CellList[row][col].tL = tlV;
			CellList[row][col].tR = trV;
			CellList[row][col].bR = brV;
			CellList[row][col].bL = blV;

			//Note: These are the points that work, my guess is that the value's above weren't representing what I expected

			float xMax = tR.Pos.X();
			float xMin = bL.Pos.X();

			float yMax = tL.Pos.Y();
			float yMin = tL.Pos.Y();

			float zMax = bL.Pos.Z();
			float zMin = tR.Pos.Z();


			// Y, tests against all 4 corners
			if (tR.Pos.Y() > yMax)
				yMax = tR.Pos.Y();

			if (bR.Pos.Y() > yMax)
				yMax = bR.Pos.Y();

			if (bL.Pos.Y() > yMax)
				yMax = bL.Pos.Y();

			if (bL.Pos.Y() < yMin)
				yMin = bL.Pos.Y();

			if (tR.Pos.Y() < yMin)
				yMin = tR.Pos.Y();

			if (bR.Pos.Y() < yMin)
				yMin = bR.Pos.Y();

			CellList[row][col].Max = Vect(xMax, yMax, zMax);
			CellList[row][col].Min = Vect(xMin, yMin, zMin);
		}
	}

	//After  each triagle's face norm is computed and stored I loop through it again to find the vector normals
	for (int row = 1; row < height-1; row++)
	{
		for (int col = 1; col < height-1; col++)
		{
			Vect TopLeft = SumNorm[row-1][col-1];
			Vect Top = SumNorm[row-1][col];
			Vect Left = SumNorm[row][col-1];
			Vect TopRight = SumNorm[row-1][col+1];
			Vect Right = SumNorm[row][col+1];
			Vect BotRight = SumNorm[row+1][col+1];
			Vect Bot = SumNorm[row+1][col];
			Vect BotLeft = SumNorm[row + 1][col-1];;

			//Now Save the actual norm
			CellList[row][col].tLNorm = (TopLeft + Top + Left + SumNorm[row][col]).norm();
			CellList[row][col].tRNorm = (Top + TopRight + Right + SumNorm[row][col]).norm();
			CellList[row][col].bRNorm = (Right + BotRight + Bot + SumNorm[row][col]).norm();
			CellList[row][col].bLNorm = (Bot + BotRight + BotLeft + SumNorm[row][col]).norm();
		}
	}

	pModTerrain = new Model(pVerts, numVerts, pTriList, numTri);
	myMap = heightMap;

	size = CellList[0][0].Max.X() - CellList[0][0].Min.X();
	TerrainTest = new GraphicObject_TextureLight(ShaderManager::Get(ShaderManager::DefaultShaders::PolliwogTextureLightRender), pModTerrain, texture);
}

int Terrain::TexelIndex(int side, int row, int col) const
{
	size_t pixel_width = 4;	// 4 bytes RGBA per pixel
	return pixel_width * (row * side + col);
}

void Terrain::Draw()   
{
	TerrainTest->Render(SceneManager::getCurrentScene()->getCamera());
}

// Get Methods
const Cell& Terrain::GetCell(int x, int y)
{
	if (x >= (int)CellList[0].size())
		x = CellList[0].size() - 1;
	if (y >= (int)CellList[0].size())
		y = CellList[0].size() - 1;
	return CellList[x][y];
}

/// <summary>
/// \ingroup TERRAIN
/// \brief Returns the Cell Below an Objects position
/// </summary>
const std::pair<int, int> Terrain::GetCellBelow(const Vect& pos)
{
	// Get Cell distance relative the 'pos' and the corner of the grid (anchor point)
	float c = pos.X() - CellList[0][0].Min.X();
	float r = pos.Z() - CellList[0][0].Min.X();

	//Devide by Cell Size to get the final row and col
	int col = (int)(c / size);
	int row = (int)(r / size);

	//Check for if its outside or inside the terrain bounds
	if (col >= SideNum)
		col = SideNum - 1;
	else if (col < 0)
		col = 0;

	if (row >= SideNum)
		row = SideNum - 1;
	else if (row < 0)
		row = 0;

	return { row, col };
}

// Visualize Cell
void Terrain::visualizeCellBelow(Vect pos)
{
	std::pair<int, int> Cell = GetCellBelow(pos);

	//Visualize each point
	Vect A = CellList[Cell.first][Cell.second].Min;
	Visualizer::ShowPoint(A, Colors::Aqua);

	Vect C = CellList[Cell.first][Cell.second].Max;
	Visualizer::ShowPoint(C, Colors::Crimson);

	// Outside points
	Vect A2 = CellList[Cell.first][Cell.second].Min;
	A2.X() += size;
	Visualizer::ShowPoint(A2, Colors::Pink);

	Vect C2 = CellList[Cell.first][Cell.second].Max;
	C2.X() -= size;
	Visualizer::ShowPoint(C2, Colors::Pink);

	// AABB Box
	Visualizer::ShowMinMax(CellList[Cell.first][Cell.second].Max, CellList[Cell.first][Cell.second].Min, Colors::Azure);
}

void Terrain::visualizeWireFramePoints(Vect pos)
{
	std::pair<int, int> Cell = GetCellBelow(pos);

	Vect Cmin = CellList[Cell.first][Cell.second].tL;
	Visualizer::ShowPoint(Cmin, Colors::Pink);

	Vect A = CellList[Cell.first][Cell.second].tR;
	Visualizer::ShowPoint(A, Colors::Aqua);

	Vect B = CellList[Cell.first][Cell.second].bL;
	Visualizer::ShowPoint(B, Colors::Aqua);

	Vect Cmax = CellList[Cell.first][Cell.second].bR;
	Visualizer::ShowPoint(Cmax, Colors::Crimson);
}

/// <summary>
/// \ingroup TERRAIN
/// \brief Returns the object's adjusted height based on changes in the terrain.
/// </summary>
float Terrain::GetHeight(const Vect& pos)
{
	//visualizeCellBelow(pos);

	std::pair<int, int> Cell = GetCellBelow(pos);

	// Find Points (ON WIREFRAME)
	Vect Cmin = CellList[Cell.first][Cell.second].tL;

	Vect A = CellList[Cell.first][Cell.second].tR;

	Vect B = CellList[Cell.first][Cell.second].bL;

	Vect Cmax = CellList[Cell.first][Cell.second].bR;


	Vect V = (pos - A);

	float beta;
	float gamma;
	float h;

	if (-V.X() < V.Z())
	{
		// Set up stuff for Q
		Vect v0 = B - A;
		Vect v1 = Cmax - B;
		Vect v2 = pos - A;

		float a = v0.dot(v0);
		float b = v1.dot(v0);
		float c = v1.dot(v1);
		float d = v2.dot(v0);
		float e = v2.dot(v1);

		// Find Beta and Gamma for Q
		beta = ((d*c) - (b*e)) / ((a * c) - (b * b));
		gamma = ((a * e) - (d * b)) / ((a * c) - (b * b));

		// Grab hieght based on Q calculation
		h = A.Y() + ((B.Y() - A.Y()) * beta) + ((Cmax.Y() - B.Y()) * gamma);

		Vect realpos = pos;
		realpos.Y() = CellList[Cell.first][Cell.second].Min.Y();
		Visualizer::ShowPoint(realpos, Colors::Blue);
	}
	else
	{
		Vect v0 = B - A;
		Vect v1 = Cmin - B;
		Vect v2 = pos - A;

		float a = v0.dot(v0);
		float b = v1.dot(v0);
		float c = v1.dot(v1);
		float d = v2.dot(v0);
		float e = v2.dot(v1);

		beta = ((d * c) - (b * e)) / ((a * c) - (b * b));
		gamma = ((a * e) - (d * b)) / ((a * c) - (b * b));

		h = A.Y() + ((B.Y() - A.Y()) * beta) + ((Cmin.Y() - B.Y()) * gamma);

		Vect realpos = pos;
		realpos.Y() = CellList[Cell.first][Cell.second].Min.Y();
		Visualizer::ShowPoint(realpos, Colors::Yellow);
	}

	if (Cell.first == 0 || Cell.second == 0 || Cell.first == SideNum-1 || Cell.second == SideNum - 1)
	{
		return 0;
	}

	return h;
}

// Calculated Vector Norm with the face normals of the triangles surrounding each vector

/// <summary>
/// \ingroup TERRAIN
/// \brief Returns the projected surface normal used to determine the object's rotation.
/// </summary>
const Vect& Terrain::GetNormal(const Vect& pos)
{
	std::pair<int, int> Cell = GetCellBelow(pos);

	// Find Points (ON WIREFRAME)
	const Vect Cmin = CellList[Cell.first][Cell.second].tL;
	const Vect NormCmin = CellList[Cell.first][Cell.second].tLNorm; //Felt easiest to just store each norm inside the Cell Struct

	const Vect A = CellList[Cell.first][Cell.second].tR;
	const Vect NormA = CellList[Cell.first][Cell.second].tRNorm;

	const Vect B = CellList[Cell.first][Cell.second].bL;
	const Vect NormB = CellList[Cell.first][Cell.second].bLNorm;

	const Vect Cmax = CellList[Cell.first][Cell.second].bR;
	const Vect NormCmax = CellList[Cell.first][Cell.second].bRNorm;

	const Vect V = (pos - A);

	float beta;
	float gamma;
	Vect norm;
	Vect normPos;

	if (-V.X() < V.Z())
	{
		// Set up stuff for Q
		Vect v0 = B - A;
		Vect v1 = Cmax - B;
		Vect v2 = pos - A;

		float a = v0.dot(v0);
		float b = v1.dot(v0);
		float c = v1.dot(v1);
		float d = v2.dot(v0);
		float e = v2.dot(v1);

		// Find Beta and Gamma for Q
		beta = ((d * c) - (b * e)) / ((a * c) - (b * b));
		gamma = ((a * e) - (d * b)) / ((a * c) - (b * b));

		// Grab hieght based on Q calculation
		norm = NormA + ((NormB - NormA) * beta) + ((NormCmax - NormB) * gamma);
		normPos = A + ((B - A) * beta) + ((Cmax - B) * gamma);

		Vect line = pos;
		line.Y() = CellList[Cell.first][Cell.second].Min.Y();
		//Visualizer::ShowPoint(pos, line, Colors::Blue);
		//Visualizer::ShowNorm(normPos, norm, Colors::DeepPink);
	}

	else
	{
		const Vect v0 = B - A;
		const Vect v1 = Cmin - B;
		const Vect v2 = pos - A;

		float a = v0.dot(v0);
		float b = v1.dot(v0);
		float c = v1.dot(v1);
		float d = v2.dot(v0);
		float e = v2.dot(v1);    

		beta = ((d * c) - (b * e)) / ((a * c) - (b * b));
		gamma = ((a * e) - (d * b)) / ((a * c) - (b * b));

		norm = NormA + ((NormB - NormA) * beta) + ((NormCmin - NormB) * gamma);
		normPos = A + ((B - A) * beta) + ((Cmin - B) * gamma);

		Vect line = pos;
		line.Y() = CellList[Cell.first][Cell.second].Min.Y();
		//Visualizer::ShowPoint(pos, line, Colors::Yellow);
		//Visualizer::ShowNorm(normPos, norm, Colors::DeepPink);
	}

	if (Cell.first == 0 || Cell.second == 0 || Cell.first == SideNum - 1 || Cell.second == SideNum - 1)
	{
		return Vect(0, -1, 0);
	}
	return norm;
}


Terrain::~Terrain()
{
	delete[] pVerts;
	delete[] pTriList;

	delete pModTerrain;
	delete testBox;
	delete TerrainTest;
}