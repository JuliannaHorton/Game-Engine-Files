#include "Image.h"
#include "RenderAttorney.h"
#include "../Finalsprint/SpriteShader.h"

Image::Image(Texture* pTexture, RECT size)
	:CutRect(size), pText(pTexture)
{
	//Calculae Screen size
	float width = (float)size.right;
	float height = (float)size.bottom;


	Matrix scale = Matrix(SCALE, width, height, 1); //This iw
	Matrix Rot = Matrix(ROT_Y, 3.14f);
	Matrix trans = Matrix(TRANS, x, y, 5.0f);

	World = scale * Rot * trans;
}

void Image::setWorld(Matrix w)
{
	World = w;
}

void Image::setRectangle(int x, int y, int w, int h)
{
	CutRect.left = x;
	CutRect.top = y;
	CutRect.right = w;
	CutRect.bottom = h;
};

void Image::Render(SpriteShader* shader, Matrix planeWorld)
{
	shader->SendWorldandMaterial(planeWorld, pText, CutRect); //This is an easy fix, but my brain feels broken (the height and width are swapped)
}