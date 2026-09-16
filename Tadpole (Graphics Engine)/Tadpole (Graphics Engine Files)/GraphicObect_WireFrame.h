// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_WireFrame
#define _GraphicObject_WireFrame

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class Camera;

class GraphicObject_WireFrame : public GraphicObject_Base
{
public:
	GraphicObject_WireFrame(const GraphicObject_WireFrame&) = delete;				 // Copy constructor
	GraphicObject_WireFrame(GraphicObject_WireFrame&&) = default;                    // Move constructor
	GraphicObject_WireFrame& operator=(const GraphicObject_WireFrame&) & = default;  // Copy assignment operator
	GraphicObject_WireFrame& operator=(GraphicObject_WireFrame&&) & = default;       // Move assignment operator
	~GraphicObject_WireFrame();		  											 // Destructor

	GraphicObject_WireFrame() = delete;

	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render(Camera* mCam) override;

	GraphicObject_WireFrame(ShaderColor* shader, Model* mod);

private:
	ShaderColor* pShader;

	//Vect							Color;
	Vect* MeshColors;

	Matrix							World;

};

#endif _GraphicObject_WireFrame
