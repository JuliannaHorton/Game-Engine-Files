#pragma once
// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_TextureLight
#define _GraphicObject_TextureLight

#include "GraphicObject_Base.h"
#include "Vect.h"

class ShaderTextureLight;
class Texture;
class Camrra;

class GraphicObject_TextureLight : public GraphicObject_Base
{
public:
	GraphicObject_TextureLight(const GraphicObject_TextureLight&) = delete;				 // Copy constructor
	GraphicObject_TextureLight(GraphicObject_TextureLight&&) = default;                    // Move constructor
	GraphicObject_TextureLight& operator=(const GraphicObject_TextureLight&) & = default;  // Copy assignment operator
	GraphicObject_TextureLight& operator=(GraphicObject_TextureLight&&) & = default;       // Move assignment operator
	~GraphicObject_TextureLight();		  											 // Destructor

	GraphicObject_TextureLight() = delete;

	void SetLightMaterial(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetLightMaterial(Texture* tex, const Vect& amb, const Vect& dif, const Vect& sp, int num); //Going to keep this as an option incase of multiple meshes

	void SetWorld(const Matrix& m);
	const Matrix& getWorld() { return World; };
	virtual void Render(Camera* mCam) override;

	GraphicObject_TextureLight(ShaderBase* shader, Model* mod, Texture* tex);

	Model* getModel();

private:
	ShaderTextureLight* pShader;
	Matrix World;

	Texture** pMeshTextures;
	Vect* MeshAmbients;
	Vect* MeshDiffuses;
	Vect* MeshSpeculars;
	
	Model* myModel;

};

#endif _GraphicObject_TextureLight
