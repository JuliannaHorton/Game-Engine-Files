#pragma once
#pragma once

#ifndef _SkyBox
#define _SkyBox

#include "Matrix.h"

class Model;
class ShaderTexture;
class Texture;

struct ID3D11DeviceContext;
struct ID3D11Device;

class SkyBox : public Align16
{
private:
	Model* pPlane;

public:
	SkyBox(const SkyBox&) = delete;				// Copy constructor
	SkyBox(Model&&) = delete;						// Move constructor
	SkyBox& operator=(const SkyBox&) & = delete;  // Copy assignment operator
	SkyBox& operator=(SkyBox&&) & = delete;       // Move assignment operator
	~SkyBox();

	SkyBox(ShaderTexture* shader, Texture* tex, int size);

	ShaderTexture* pShader;
	Texture* pTex;

	Matrix World;

	void Render();
};

#endif _SkyBox
