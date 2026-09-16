// FlatPlane.h
// Berthiaume Jan 2017

#include <d3d11.h>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"

#ifndef _Mirror
#define _Mirror
class FlatPlane;
class ShaderBase;
class ShaderColorLight;
struct ID3D11DeviceContext;
struct ID3D11Device;

class Mirror
{
private:
	FlatPlane* pPlane;
	Matrix ReflectionMat;
	Matrix ReflectionDir = Matrix(IDENTITY);
	Matrix Pos;

	//Important buffera
	ID3D11DepthStencilState* MarkMirrorDSS;
	ID3D11DepthStencilState* DrawReflectionDSS;

	ID3D11RasterizerState* FrontFaceAsCCWRS;
	ID3D11RasterizerState* MirrorFrontFaceAsClockWiseRS;

	ID3D11BlendState* NoWriteToRenderTargetBS;
	ID3D11BlendState* TransparentBS;

public:
	Mirror(const Mirror&) = delete;				// Copy constructor
	Mirror(FlatPlane&&) = delete;                    // Move constructor
	Mirror& operator=(const Mirror&) & = delete;  // Copy assignment operator
	Mirror& operator=(Mirror&&) & = delete;       // Move assignment operator
	~Mirror();

	Mirror(FlatPlane* plane);

	void SetReflection(Matrix Location);
	Matrix GetReflection();

	void Step2(ShaderColorLight* s);
	void Step4( ShaderColorLight* s);
	void Render();

};

#endif _Mirror
