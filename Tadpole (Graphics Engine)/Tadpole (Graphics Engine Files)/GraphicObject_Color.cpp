#include "GraphicObject_Color.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>
#include "Camera.h"

#include "../Finalsprint/ModelAttorney.h"

GraphicObject_Color::GraphicObject_Color(ShaderBase* shader,  Model* mod)
{
	SetModel(mod );
	myModel = mod;
	pShader = (ShaderColor*) shader;

	//Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);

	//Loops through meshes 
	int n = mod->GetMeshCount();
	MeshColors = new Vect[n];
	for (int i = 0; i < n; i++)
		MeshColors[i] = Vect(0, 0, 0);
}

GraphicObject_Color::~GraphicObject_Color()
{
	delete[] MeshColors; //Delete the list of meshes 
}

Model* GraphicObject_Color::getModel()
{
	return myModel;
}

void GraphicObject_Color::SetColor(const Vect& col)  //Set color for all
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		MeshColors[i] = col;
}

void GraphicObject_Color::SetColor(const Vect& col, int meshnum) //Set color for a specific mesh
{
	assert(pModel->ValidMeshNum(meshnum));
	MeshColors[meshnum] = col;
}

void GraphicObject_Color::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_Color::Render(Camera* mCam)
{

	ModelAttorney::SetToContext(pModel);
	pShader->SendCamMatrices(mCam->getViewMatrix(), mCam->getProjMatrix());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldColor(World, MeshColors[i]);
		pShader->SetToContext();

		ModelAttorney::RenderMesh(pModel, i);
	}
}