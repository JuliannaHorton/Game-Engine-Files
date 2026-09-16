// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Color
#define _GraphicObject_Color

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColor.h"

class Camera;

class GraphicObject_Color : public GraphicObject_Base
{
public:
	GraphicObject_Color(const GraphicObject_Color&) = delete;				 // Copy constructor
	GraphicObject_Color(GraphicObject_Color&&) = default;                    // Move constructor
	GraphicObject_Color& operator=(const GraphicObject_Color&) & = default;  // Copy assignment operator
	GraphicObject_Color& operator=(GraphicObject_Color&&) & = default;       // Move assignment operator
	~GraphicObject_Color();		  											 // Destructor

	GraphicObject_Color() = delete;

	void SetColor(const Vect& col);
	void SetColor(const Vect& col, int meshnum);
	void SetWorld(const Matrix& m);
	virtual void Render(Camera* mCam) override;

	GraphicObject_Color(ShaderBase* shader, Model* mod);

	Model* getModel();

private:
	ShaderColor*					pShader;
	
	//Vect							Color;
	Vect*							MeshColors;

	Matrix							World;

	Model* myModel;
};

#endif _GraphicObject_Color
