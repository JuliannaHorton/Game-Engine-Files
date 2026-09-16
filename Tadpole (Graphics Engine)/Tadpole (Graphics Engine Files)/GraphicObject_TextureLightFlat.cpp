#include "../Finalsprint/GraphicObject_TextureLightFlat.h"
#include "Model.h"
#include "StandardFlatPlane.h"
#include "ShaderTextureLight.h"
#include "Texture.h"
#include "Camera.h"
#include <assert.h>

//
GraphicObject_TextureLightFlat::GraphicObject_TextureLightFlat(ShaderTextureLight* shader)
{
	pShader = shader;
	pTexture = nullptr;

	World = Matrix(IDENTITY);
	myPlane = new FlatPlane(3000, 1, 1);
}


void GraphicObject_TextureLightFlat::SetLightMaterial(Texture* tex, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pTexture = tex;
	MeshAmbients = amb;
	MeshDiffuses = dif;
	MeshSpeculars = sp;
}

GraphicObject_TextureLightFlat::~GraphicObject_TextureLightFlat()
{
	delete myPlane;
}


void GraphicObject_TextureLightFlat::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TextureLightFlat::Render(Camera* mCam)
{

	Vect eyepos;
	mCam->getPos(eyepos);

	pShader->SendCamMatrices(mCam->getViewMatrix(), mCam->getProjMatrix());
	pShader->SendLightParameters(eyepos);

	pShader->SendWorldAndMaterial(World, MeshAmbients, MeshDiffuses, MeshSpeculars, pTexture);
	pShader->SetToContext();
	myPlane->Render();
}