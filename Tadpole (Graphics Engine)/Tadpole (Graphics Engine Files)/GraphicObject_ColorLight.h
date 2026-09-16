// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Light
#define _GraphicObject_Light

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"

class Camera;

class GraphicObject_Light : public GraphicObject_Base
{
public:
	GraphicObject_Light(const GraphicObject_Light&) = delete;				 // Copy constructor
	GraphicObject_Light(GraphicObject_Light&&) = default;                    // Move constructor
	GraphicObject_Light& operator=(const GraphicObject_Light&) & = default;  // Copy assignment operator
	GraphicObject_Light& operator=(GraphicObject_Light&&) & = default;       // Move assignment operator
	~GraphicObject_Light();		  											 // Destructor

	GraphicObject_Light() = delete;

	void SetMaterials(const Vect& amb, const Vect& dif, const Vect& sp);
	void SetMaterials(const Vect& amb, const Vect& dif, const Vect& sp, int num);

	void SetWorld(const Matrix& m);
	virtual void Render(Camera* mCam) override;

	GraphicObject_Light(ShaderColorLight* shader, Model* mod);

	Model* getModel();

private:
	ShaderColorLight* pShader;
	Vect							Color;
	Matrix							World;

	Vect* MeshAmbients;
	Vect* MeshDiffuses;
	Vect* MeshSpeculars;

	Model* myModel;

};

#endif _GraphicObject_Light
