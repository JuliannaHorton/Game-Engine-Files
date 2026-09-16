#include "GraphicObject_WireFrame.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>
#include "Camera.h"
#include "../Finalsprint/RenderAttorney.h"

#include "../Finalsprint/ModelAttorney.h"

GraphicObject_WireFrame::GraphicObject_WireFrame(ShaderBase* shader, Model* mod, Vect col)
{
	SetModel(mod);
	myModel = mod;

	//assert(typeid(shader) == typeid(ShaderColor) && "Not the expected shader, please use PolliwogColorRender");
	pShader = (ShaderColor*)shader;

	Color = col;
	World = Matrix(IDENTITY);

	//Loops through meshes 
	int n = mod->GetMeshCount();
	MeshColors = new Vect[n];
	for (int i = 0; i < n; i++)
		MeshColors[i] = col;
}

GraphicObject_WireFrame::~GraphicObject_WireFrame()
{
	delete[] MeshColors; //Delete the list of meshes 
}

Model* GraphicObject_WireFrame::getModel()
{
	return myModel;
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