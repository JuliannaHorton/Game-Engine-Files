#pragma once
// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_TextureLightFlat
#define _GraphicObject_TextureLightFlat

#include "GraphicObject_Base.h"
#include "Vect.h"

class ShaderTextureLight;
class Texture;
class FlatPlane;

class GraphicObject_TextureLightFlat : public GraphicObject_Base
{
public:
	GraphicObject_TextureLightFlat(const GraphicObject_TextureLightFlat&) = delete;				 // Copy constructor
	GraphicObject_TextureLightFlat(GraphicObject_TextureLightFlat&&) = default;                    // Move constructor
	GraphicObject_TextureLightFlat& operator=(const GraphicObject_TextureLightFlat&) & = default;  // Copy assignment operator
	GraphicObject_TextureLightFlat& operator=(GraphicObject_TextureLightFlat&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLightFlat();		  											 // Destructor

	GraphicObject_TextureLightFlat() = delete;

	GraphicObject_TextureLightFlat(ShaderTextureLight* shader);

	void SetWorld(const Matrix& m);
	virtual void Render(Camera* mCam) override;

	void SetLightMaterial(Texture* tex, const Vect& amb, const Vect& dif, const Vect& sp);

private:
	ShaderTextureLight* pShader;
	FlatPlane* myPlane;
	Matrix World;

	Vect MeshAmbients;
	Vect MeshDiffuses;
	Vect MeshSpeculars;

	Texture* pTexture;

};

#endif _GraphicObject_Texture
