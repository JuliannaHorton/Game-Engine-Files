#include "../Finalsprint/GraphicObject_TextureFlat.h"
#include "Model.h"
#include "StandardFlatPlane.h"
#include "ShaderTexture.h"
#include "Texture.h"
#include <assert.h>
#include "Camera.h"

//
GraphicObject_TextureFlat::GraphicObject_TextureFlat(ShaderTexture* shader)
{
	pShader = shader;
	pTexture = nullptr;

	World = Matrix(IDENTITY);
	myPlane = new FlatPlane(100, 1, 1);
}

GraphicObject_TextureFlat::~GraphicObject_TextureFlat()
{
	delete myPlane;
}

void GraphicObject_TextureFlat::SetTexture(Texture* tex)
{
	pTexture = tex;
}


void GraphicObject_TextureFlat::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_TextureFlat::Render(Camera* mCam)
{

	pShader->SendWorldandTexture(World, pTexture);
	pShader->SendCamMatrices(mCam->getProjMatrix(), mCam->getOrthoMatrix());
	pShader->SetToContext();
	myPlane->Render();
}