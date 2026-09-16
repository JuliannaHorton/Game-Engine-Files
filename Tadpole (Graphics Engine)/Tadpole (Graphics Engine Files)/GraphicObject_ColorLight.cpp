#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>

#include "../Finalsprint/ModelAttorney.h"
#include "Camera.h"
#include "../src/d3dUtil.h"

GraphicObject_Light::GraphicObject_Light(ShaderColorLight* shader, Model* mod)
{
	SetModel(mod);
	myModel = mod;
	pShader = shader;

	Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	//Loop through the list of lightinf effects
	int n = mod->GetMeshCount();
	MeshAmbients = new Vect[n];
	MeshDiffuses = new Vect[n];
	MeshSpeculars = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		MeshAmbients[i] = Colors::White;
		MeshDiffuses[i] = Colors::White;
		MeshSpeculars[i] = Vect(1, 1, 1, 100);
	}
}

//Delete everything 
GraphicObject_Light::~GraphicObject_Light()
{
	delete[] MeshAmbients;
	delete[] MeshDiffuses;
	delete[] MeshSpeculars;
}

Model* GraphicObject_Light::getModel()
{
	return myModel;
}

void GraphicObject_Light::SetMaterials(const Vect& amb, const Vect& dif, const Vect& sp) //Set them for the whole mesh
{
	int n = pModel->GetMeshCount();

	for (int i = 0; i < n; i++)
	{
		MeshAmbients[i] = amb;
		MeshDiffuses[i] = dif;
		MeshSpeculars[i] = sp;
	}
}

void GraphicObject_Light::SetMaterials(const Vect& amb, const Vect& dif, const Vect& sp, int num) //Set them for a specific mesh
{
	assert(pModel->ValidMeshNum(num));

	MeshAmbients[num] = amb;
	MeshDiffuses[num] = dif;
	MeshSpeculars[num] = sp;
}

void GraphicObject_Light::SetWorld(const Matrix& m) //Can set world at anytime
{
	World = m;
}

void GraphicObject_Light::Render(Camera* mCam)
{
	ModelAttorney::SetToContext(pModel);
	int n = pModel->GetMeshCount();

	Vect eyepos;
	mCam->getPos(eyepos);
	pShader->SendCamMatrices(mCam->getViewMatrix(), mCam->getProjMatrix());
	pShader->SendLightParameters(eyepos);

	for (int i = 0; i < n; i++) //Loops through meshes for render
	{
		pShader->SendWorldAndMaterial(World, MeshAmbients[i], MeshDiffuses[i], MeshSpeculars[i]);
		pShader->SetToContext();

		ModelAttorney::RenderMesh(pModel, i);
	}

}