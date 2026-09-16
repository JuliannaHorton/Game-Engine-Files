#include "SpriteFlatPlane.h"
#include "Model.h"
#include "d3dUtil.h"

#include "../Finalsprint/ModelAttorney.h"

SpriteFlatPlane::SpriteFlatPlane(float size, float hrep, float vrep)
{
	int nverts = 4;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 2;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	float c = (size) / 2;

	//Altered to be more like a wall
	pVerts[0].set(-c, -c, 0, hrep, vrep, 0, 0, 1); // x, y, z
	pVerts[1].set(-c, c, 0, hrep, 0, 0, 0, 1);
	pVerts[2].set(c, c, 0, 0, 0, 0, 0, 1);
	pVerts[3].set(c, -c, 0, 0, vrep, 0, 0, 1);

	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	pPlane = new Model(pVerts, nverts, pTriList, ntri);
	//pPlane = new Model( dev, Model::PreMadeModels::UnitSphere);

	delete[] pVerts;
	delete[] pTriList;
}

SpriteFlatPlane::~SpriteFlatPlane()
{
	delete pPlane;
}

void SpriteFlatPlane::Render()
{

	ModelAttorney::SetToContext(pPlane);
	pPlane->Render();
}