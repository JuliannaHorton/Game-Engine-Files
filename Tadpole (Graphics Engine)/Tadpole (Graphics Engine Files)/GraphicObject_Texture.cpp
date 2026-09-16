#include "../Finalsprint/GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderTexture.h"
#include "Texture.h"
#include <assert.h>
#include "Camera.h"

#include "../Finalsprint/ModelAttorney.h"

//
GraphicObject_Texture::GraphicObject_Texture(ShaderTexture* shader, Model* mod, Texture* tex)
{
	SetModel(mod);
	myModel = mod;
	pShader = shader;

	Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);
	
	///pTexture = new Texture(md3dDevice, L"../Assets/Textures/CubeFaces.tga"); //pTexture will basically be our default

	int n = mod->GetMeshCount();
	pMeshTextures = new Texture*[n];
	for (int i = 0; i < n; i++)
		pMeshTextures[i] = tex;
}


GraphicObject_Texture::~GraphicObject_Texture()
{
	delete[] pMeshTextures;
}

Model* GraphicObject_Texture::getModel()
{
	return myModel;
}


void GraphicObject_Texture::SetColor(const Vect& col)
{
	Color = col;
}

//void GraphicObject_Texture::SetTexture(Texture* tex)
//{
//	pTexture = tex;
//}


void GraphicObject_Texture::SetTexture(Texture* tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		pMeshTextures[i] = tex;
}

void GraphicObject_Texture::SetTexture(Texture* tex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	pMeshTextures[meshnum] = tex;
}



void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Texture::Render(Camera* mCam)
{
	ModelAttorney::SetToContext(pModel);
	pShader->SendCamMatrices(mCam->getViewMatrix(), mCam->getProjMatrix());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SendWorldandTexture(World, pMeshTextures[i]);
		pShader->SetToContext();
		ModelAttorney::RenderMesh(pModel, i);
	}
}