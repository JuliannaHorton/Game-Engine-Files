#pragma once
// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Texture
#define _GraphicObject_Texture

#include "GraphicObject_Base.h"
#include "Vect.h"

class ShaderTexture;
class Texture;
class Camera;

class GraphicObject_Texture : public GraphicObject_Base
{
public:
	GraphicObject_Texture(const GraphicObject_Texture&) = delete;				 // Copy constructor
	GraphicObject_Texture(GraphicObject_Texture&&) = default;                    // Move constructor
	GraphicObject_Texture& operator=(const GraphicObject_Texture&) & = default;  // Copy assignment operator
	GraphicObject_Texture& operator=(GraphicObject_Texture&&) & = default;       // Move assignment operator
	~GraphicObject_Texture();		  											 // Destructor

	GraphicObject_Texture() = delete;

	void SetColor(const Vect& col);
	void SetWorld(const Matrix& m);
	virtual void Render(Camera* mCam) override;

	GraphicObject_Texture(ShaderTexture* shader, Model* mod, Texture* tex);

	void SetTexture(Texture* tex);
	void SetTexture(Texture* tex, int meshnum);
	Model* getModel();


private:
	ShaderTexture* pShader;
	Vect Color;
	Matrix World;
	Texture** pMeshTextures;

	Texture* pTexture;

	Model* myModel;

};

#endif _GraphicObject_Texture
