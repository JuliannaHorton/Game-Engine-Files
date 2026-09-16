#pragma once
// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_TextureFlat
#define _GraphicObject_TextureFlat

#include "GraphicObject_Base.h"
#include "Vect.h"

class ShaderTexture;
class Texture;
class FlatPlane;

class GraphicObject_TextureFlat : public GraphicObject_Base
{
public:
	GraphicObject_TextureFlat(const GraphicObject_TextureFlat&) = delete;				 // Copy constructor
	GraphicObject_TextureFlat(GraphicObject_TextureFlat&&) = default;                    // Move constructor
	GraphicObject_TextureFlat& operator=(const GraphicObject_TextureFlat&) & = default;  // Copy assignment operator
	GraphicObject_TextureFlat& operator=(GraphicObject_TextureFlat&&) & = default;       // Move assignment operator
	~GraphicObject_TextureFlat();		  											 // Destructor

	GraphicObject_TextureFlat() = delete;

	void SetWorld(const Matrix& m);
	virtual void Render(Camera* mCam) override;

	GraphicObject_TextureFlat(ShaderTexture* shader);

	void SetTexture(Texture* tex);

private:
	ShaderTexture* pShader;
	FlatPlane* myPlane;
	Matrix World;

	Texture* pTexture;

};

#endif _GraphicObject_Texture
