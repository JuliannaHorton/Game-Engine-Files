#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, 1, 0, 0, 0, 1);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red);
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitBoxSixFacesTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;

	//Back
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 0.5f, 0.375f);
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0.5f, 0.625f);
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0.75f, 0.625f);
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 0.75f, 0.375f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Forward
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.25f, 0.375f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.25f, 0.625f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 0.625f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 0.375f);

	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.25f, 0.375f);
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0.5f, 0.375f);
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0.5f, 0.125f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0.25f, 0.125f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.25f, 0.625f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0.25f, 0.875f);
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 0.5f, 0.875f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0.25f, 0.375f); //1
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0.25f, 0.625f); //2
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0.5f, 0.625f); //4
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 0.5f, 0.375f); //3
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 0.75f, 0.375f);
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0.75f, 0.625f);
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 0.625f);
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 0.375f);
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}

void ModelTools::CreateUnitPyramid(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 5;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.0f, +0.5f, +0.0f, 0, 0, 0, -1, 0); //Top
	pVerts[1].set(+0.5f, -0.5f, -0.5f, 0, 0, -0.5f, 0.5f, 0);
	pVerts[2].set(-0.5f, -0.5f, -0.5f, 0, 0, 0, 0.5f, 0.5f);
	pVerts[3].set(+0.5f, -0.5f, +0.5f, 0, 0, 0.5f, 0.5f, 0);
	pVerts[4].set(-0.5f, -0.5f, +0.5f, 0, 0, 0, 0.5f, -0.5f);

	// Bottom
	pTriList[0].set(2, 1, 3);
	pTriList[1].set(2, 3, 4);

	//Top
	pTriList[2].set(0, 1, 2);

	pTriList[3].set(0, 3, 1);

	pTriList[4].set(0, 4, 3);

	pTriList[5].set(0, 2, 4);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	nverts = 16;
	pVerts = new StandardVertex[nverts];

	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	int v = 0;
	int t = 0;

	//Bottom Square
	//Four points for the four points of a square
	pVerts[v + 0].set(-0.5f, -0.5f, -0.5f, 0, 0, 0, -1, 0); //x, y, z, u and v
	pVerts[v + 1].set(-0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);
	pVerts[v + 2].set(0.5f, -0.5f, 0.5f, 1, 1, 0, -1, 0);
	pVerts[v + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);

	//2 Triangles within the square
	pTriList[t++].set(v + 0, v + 2, v + 1);
	pTriList[t++].set(v + 0, v + 3, v + 2);

	v += 4;

	// Apex
	const float ax = 0.0f;
	const float ay = 0.5f;
	const float az = 0.0f;

	//Triangle Side 1 (Right)
	//Now 3 points
	pVerts[v + 0].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0.5, 0);
	pVerts[v + 1].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0.5f, 0);
	pVerts[v + 2].set(ax, ay, az, 0.5f, 0, -1, 0.5f, 0);

	pTriList[t++].set(v + 0, v + 1, v + 2);
	v += 3;

	//Triangle Side 2 (Back)
	pVerts[v + 0].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0.5f, 1);
	pVerts[v + 1].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0.5f, 1);
	pVerts[v + 2].set(ax, ay, az, 0.5f, 0, 0, 0.5f, 1);

	pTriList[t++].set(v + 0, v + 1, v + 2);
	v += 3;

	//Triangle Side 3
	pVerts[v + 0].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0.5f, 0);
	pVerts[v + 1].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0.5f, 0);
	pVerts[v + 2].set(ax, ay, az, 0.5f, 0, 1, 0.5f, 0);

	pTriList[t++].set(v + 0, v + 1, v + 2);
	v += 3;

	//Triangle Side 4
	pVerts[v + 0].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0.5f, -1);
	pVerts[v + 1].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0.5f, -1);
	pVerts[v + 2].set(ax, ay, az, 0.5f, 0, 0, 0.5f, -1);

	pTriList[t++].set(v + 0, v + 1, v + 2);
}

void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	ntri = vslice * hslice * 2;
	nverts = ntri - 2;

	pVerts = new StandardVertex[nverts];
	pTriList = new TriangleByIndex[ntri];

	const float PI = 3.14159265358979323846f;
	const float PI2 = PI * 2;
	//a radius of 1 should be fine

	int index = 0;
	for (int h = 0; h <= hslice; h++)
	{
		// v / (slices * PI) --- Longitude
		float phi = (float)h / hslice * PI; //rotation horizontally (a horitzontal slice)
		for (int v = 0; v < vslice; v++)
		{
			// v / (slices * PI2) --- Latitude
			float theta = (float)v / vslice * PI2; //rotation horizontally (a verticle slice)

			float x = sinf(phi) * cosf(theta); //x = r(sin(phi) * cos(theta))
			float z = cosf(phi);			   //z = r(cos(phi))
			float y = sinf(phi) * sinf(theta); //y = r(sin(phi) * sin(theta))


			pVerts[index].set(x, y, z, 0, 0, x, y, z); //The normals location is just the loaction of x, y, and z

			index++;
		}
	}

	index = 0;
	for (int i = 0; i < hslice; i++)
	{
		for (int j = 0; j < vslice; j++)
		{
			//Creating a "square"

			//Four points on a square
			int firstPnt = i * vslice + j;
			int secondPnt = firstPnt + vslice;
			int thirdPnt = i * vslice + (j + 1) % vslice;
			int fourthPnt = thirdPnt + vslice;

			//We need two triangles per a "square"
			pTriList[index].set(firstPnt, secondPnt, thirdPnt);
			index++;

			pTriList[index].set(thirdPnt, secondPnt, fourthPnt);
			index++;
		}
	}
}

void ModelTools::CreateUnitSphereRepTexture(int vslice, int hslice, StandardVertex*& pVerts, int& nverts, TriangleByIndex*& pTriList, int& ntri)
{
	ntri = vslice * hslice * 2;
	nverts = ntri - 2;

	pVerts = new StandardVertex[nverts];
	pTriList = new TriangleByIndex[ntri];

	const float PI = 3.14159265358979323846f;
	const float PI2 = PI * 2;
	//a radius of 1 should be fine

	int index = 0;
	for (int h = 0; h <= hslice; h++)
	{
		// v / (slices * PI) --- Longitude
		float V = (float)h / hslice;
		float phi = (float)h / hslice * PI; //rotation horizontally (a horitzontal slice)
		for (int v = 0; v < vslice; v++)
		{
			// v / (slices * PI2) --- Latitude
			float U = (float)v / vslice;
			float theta = (float)v / vslice * PI2; //rotation horizontally (a verticle slice)

			float x = sinf(phi) * cosf(theta); //x = r(sin(phi) * cos(theta))
			float z = cosf(phi);			   //z = r(cos(phi))
			float y = sinf(phi) * sinf(theta); //y = r(sin(phi) * sin(theta))

			pVerts[index].set(x, y, z, U, V, x, y, z); //The normals location is just the loaction of x, y, and z

			index++;
		}
	}

	index = 0;
	for (int i = 0; i < hslice; i++)
	{
		for (int j = 0; j < vslice; j++)
		{
			//Creating a "square"

			//Four points on a square
			int firstPnt = i * vslice + j;
			int secondPnt = firstPnt + vslice;
			int thirdPnt = i * vslice + (j + 1) % vslice;
			int fourthPnt = thirdPnt + vslice;

			//We need two triangles per a "square"
			pTriList[index].set(firstPnt, secondPnt, thirdPnt);
			index++;

			pTriList[index].set(thirdPnt, secondPnt, fourthPnt);
			index++;
		}
	}
}



