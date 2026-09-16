#include "GraphicObject_TextureLight.h"
#include "Model.h"
#include "Texture.h"
#include "ModelAttorney.h"
#include "../Finalsprint/ShaderTextureLight.h"
#include <assert.h>
#include "Camera.h"
#include "../src/d3dUtil.h"

GraphicObject_TextureLight::GraphicObject_TextureLight(ShaderBase* shader, Model* mod, Texture* tex)
{
	SetModel(mod);
	myModel = mod;
	//assert(typeid(shader) == typeid(ShaderTextureLight) && "Not the expected shader, please use PolliwogTextureLightRender");
	pShader = (ShaderTextureLight*)shader;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	pMeshTextures = new Texture* [n];
	MeshAmbients = new Vect[n];
	MeshDiffuses = new Vect[n];
	MeshSpeculars = new Vect[n];
	for (int i = 0; i < n; i++)
	{
		pMeshTextures[i] = tex;
		MeshAmbients[i] = Colors::White;
		MeshDiffuses[i] = Colors::White;
		MeshSpeculars[i] = Vect(1, 1, 1, 100);
	}
}

GraphicObject_TextureLight::~GraphicObject_TextureLight()
{
	delete[] pMeshTextures;
	delete[] MeshAmbients;
	delete[] MeshDiffuses;
	delete[] MeshSpeculars;
}

Model* GraphicObject_TextureLight::getModel()
{
	return myModel;
}


void GraphicObject_TextureLight::SetLightMaterial(const Vect& amb, const Vect& dif, const Vect& sp)
{
	int n = pModel->GetMeshCount();

	for (int i = 0; i < n; i++)
	{
		MeshAmbients[i] = amb;
		MeshDiffuses[i] = dif;
		MeshSpeculars[i] = sp;
	}
}

void GraphicObject_TextureLight::SetLightMaterial(Texture* tex, const Vect& amb, const Vect& dif, const Vect& sp, int num)
{
	assert(pModel->ValidMeshNum(num));

	pMeshTextures[num] = tex;
	MeshAmbients[num] = amb;
	MeshDiffuses[num] = dif;
	MeshSpeculars[num] = sp;
}

void GraphicObject_TextureLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TextureLight::Render(Camera* mCam)
{
	int n = pModel->GetMeshCount();
	
	Vect eyepos;
	mCam->getPos(eyepos);
	pShader->SendCamMatrices(mCam->getViewMatrix(), mCam->getProjMatrix());
	pShader->SendLightParameters(eyepos);

	ModelAttorney::SetToContext(pModel);
	for (int i = 0; i < n; i++)
	{
		pShader->SendWorldAndMaterial(World, MeshAmbients[i], MeshDiffuses[i], MeshSpeculars[i], pMeshTextures[i]);
		pShader->SetToContext();

		ModelAttorney::RenderMesh(pModel, i);
	}


}