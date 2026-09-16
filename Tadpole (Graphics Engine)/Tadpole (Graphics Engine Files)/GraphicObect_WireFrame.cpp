#include "GraphicObect_WireFrame.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>
#include "Camera.h"
#include "../DX Application/RenderAttorney.h"

#include "../DX Application/ModelAttorney.h"

GraphicObject_WireFrame::GraphicObject_WireFrame(ShaderColor* shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	//Loops through meshes 
	int n = mod->GetMeshCount();
	MeshColors = new Vect[n];
	for (int i = 0; i < n; i++)
		MeshColors[i] = Vect(0, 0, 0);
}

GraphicObject_WireFrame::~GraphicObject_WireFrame()
{
	delete[] MeshColors; //Delete the list of meshes 
}

void GraphicObject_WireFrame::SetColor(const Vect& col)  //Set color for all
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

void GraphicObject_WireFrame::SetColor(const Vect& col, int meshnum) //Set color for a specific mesh
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum] = col;
}

void GraphicObject_WireFrame::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_WireFrame::Render(Camera* mCam)
{
	RenderAttorney::GraphicObjects::SetToWireframe();

	pShader->SetToContext();
	pShader->SendCamMatrices(mCam->getViewMatrix(), mCam->getProjMatrix());
	ModelAttorney::SetToContext(pModel);

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(World, MeshColors[i]);
		pShader->SetToContext();

		ModelAttorney::RenderMesh(pModel, i);
	}

	RenderAttorney::GraphicObjects::SetToSolidframe();
}