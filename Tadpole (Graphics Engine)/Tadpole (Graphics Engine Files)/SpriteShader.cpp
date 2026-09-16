#include "SpriteShader.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

#include "Texture.h"

SpriteShader::SpriteShader()
	: ShaderBase(L"Sprite.hlsl") //having trouble makign my own hlsl file, so I'm just gonna use ColorSelected
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr = S_OK;

	// View Matruces buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

}

SpriteShader::~SpriteShader()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
}

void SpriteShader::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}


void SpriteShader::SendWorldandMaterial(const Matrix& world, Texture* tex, const RECT& size)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	float cropX = (float)size.left;
	float cropY = (float)size.top;
	float cropWidth = (float)size.right;
	float cropHeight = (float)size.bottom;

	// Pass position along with the correct width and height to the shader
	wm.CutRect = Vect(cropX, cropY, cropWidth, cropHeight);
	wm.imageWidth = tex->getWidth();
	wm.imageHeight = tex->getHeight();

	mpTextureSRV = tex->GetTexture();
	mpSamplerState = tex->GetSamplier();

	GetContext()->PSSetShaderResources(0, 1, &mpTextureSRV);
	GetContext()->PSSetSamplers(0, 1, &mpSamplerState);

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void SpriteShader::SetToContext()
{
	ShaderBase::SetToContext_VS_PS_InputLayout();

	GetContext()->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	GetContext()->VSSetConstantBuffers(1, 1, &mpBuffWordAndMaterial);

	GetContext()->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	GetContext()->PSSetConstantBuffers(1, 1, &mpBuffWordAndMaterial);
}
