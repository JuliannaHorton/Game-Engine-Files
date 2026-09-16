// FlatPlane.h
// Berthiaume Jan 2017

#ifndef _SpriteFlatPlane
#define _SpriteFlatPlane

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class SpriteFlatPlane
{
private:
	Model* pPlane;

public:
	SpriteFlatPlane(const SpriteFlatPlane&) = delete;				// Copy constructor
	SpriteFlatPlane(Model&&) = delete;                    // Move constructor
	SpriteFlatPlane& operator=(const SpriteFlatPlane&) & = delete;  // Copy assignment operator
	SpriteFlatPlane& operator=(SpriteFlatPlane&&) & = delete;       // Move assignment operator
	~SpriteFlatPlane();

	SpriteFlatPlane(float size, float hrep, float vrep);

	void Render();

};

#endif _SpriteFlatPlane
