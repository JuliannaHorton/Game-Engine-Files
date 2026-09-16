#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"
#include "Texture.h"
#include "ShaderTexture.h"
#include "../Finalsprint/ModelAttorney.h"

SkyBox::SkyBox(ShaderTexture* shader, Texture* tex, int size) //Now takes in Shader, texture, and size 
	: pShader(shader), pTex(tex)
{
	World = Matrix(IDENTITY) * Matrix(ROT_Y, -0.45f) * Matrix(ROT_X, 1.38f);
	
	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];
	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;

	//Back

	pVerts[vind].set(0.5f * size, 0.5f * size, 0.5f * size, 0.5f, 0.375f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, 0.5f * size, 0.25f, 0.375f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, 0.5f * size, 0.25f, 0.625f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, 0.5f * size, 0.5f, 0.625f);

	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Forward
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 0.75f, 0.375f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 1, 0.375f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 1, 0.625f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 0.75f, 0.625f);

	pTriList[tind].set(vind + 2, vind, vind + 1);
	pTriList[tind + 1].set(vind + 3, vind, vind + 2);

	//Left..Should be the Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 0.75f, 0.375f);
	pVerts[vind + 1].set(0.5f * size, 0.5f * size, 0.5f * size, 0.5f, 0.375f);
	pVerts[vind + 2].set(0.5f * size, -0.5f * size, 0.5f * size, 0.5f, 0.625f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 0.75f, 0.625f);

	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);


	//Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f * size, 0.5f * size, 0.5f * size, 0.25f, 0.375f);
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0, 0.375f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0, 0.625f);
	pVerts[vind + 3].set(-0.5f * size, -0.5f * size, 0.5f * size, 0.25f, 0.625f);

	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, 0.5f * size, -0.5f * size, 0.5f, 0.125f); //1
	pVerts[vind + 1].set(-0.5f * size, 0.5f * size, -0.5f * size, 0.25f, 0.125f); //2
	pVerts[vind + 2].set(-0.5f * size, 0.5f * size, 0.5f * size, 0.25f, 0.375f); //4
	pVerts[vind + 3].set(0.5f * size, 0.5f * size, 0.5f * size, 0.5f, 0.375f); //3

	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);


	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f * size, -0.5f * size, 0.5f * size, 0.5f, 0.625f);
	pVerts[vind + 1].set(-0.5f * size, -0.5f * size, 0.5f * size, 0.25f, 0.625f);
	pVerts[vind + 2].set(-0.5f * size, -0.5f * size, -0.5f * size, 0.25f, 0.875f);
	pVerts[vind + 3].set(0.5f * size, -0.5f * size, -0.5f * size, 0.5f, 0.875f);

	pTriList[tind].set(vind, vind + 2, vind + 1);
	pTriList[tind + 1].set(vind, vind + 3, vind + 2);

	pPlane = new Model(pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;

}

SkyBox::~SkyBox()
{
	delete pPlane;
}

//Now sets everything to context
void SkyBox::Render() 
{
	ModelAttorney::SetToContext(pPlane);

	pShader->SendWorldandTexture(World, pTex);
	pPlane->Render();
}