#pragma once

#ifndef _Image
#define _Image

#include "Texture.h"
#include "SpriteFlatPlane.h"
#include "ShaderTexture.h"

class SpriteShader;

class Image
{
public:
	// public methods: -------------------------------------------------------------
	Image() = default;
	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;
	~Image() = default;

	Image(Texture* pTexture, RECT size);

	const RECT& getRectangle() { return CutRect; };
	void setRectangle(int x, int y, int w, int h);
	const Matrix& getWorld() { return World; };
	void setWorld(Matrix w);

	void Render(SpriteShader* shader, Matrix planeWorld);

private:

	// data: -----------------------------------------------------------------------
	RECT CutRect;
	Texture* pText = nullptr;
	Matrix World;
};


#endif _Image