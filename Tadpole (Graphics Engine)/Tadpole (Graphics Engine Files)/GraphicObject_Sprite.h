#ifndef _GraphicObject_Sprite
#define _GraphicObject_Sprite

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "Texture.h"
#include "Image.h"
#include "../Finalsprint/SpriteShader.h"

class Camera;

class GraphicObject_Sprite : public GraphicObject_Base
{
public:
	GraphicObject_Sprite(const GraphicObject_Sprite&) = delete;				 // Copy constructor
	GraphicObject_Sprite(GraphicObject_Sprite&&) = default;                    // Move constructor
	GraphicObject_Sprite& operator=(const GraphicObject_Sprite&) & = default;  // Copy assignment operator
	GraphicObject_Sprite& operator=(GraphicObject_Sprite&&) & = default;       // Move assignment operator
	~GraphicObject_Sprite();		  											 // Destructor

	GraphicObject_Sprite(SpriteShader* shader, Image* image, RECT rect);

	virtual void Render(Camera* mCam) override;

	void SetWorld(const Matrix& m);
	void SetImageRectPos(int x, int y);
	void SetImageRectSize(int w, int h);
	const RECT& GetImageRect() { return pImage->getRectangle(); };

	void SetScale(const int w, const int h);

private:
	SpriteShader* pShader;
	SpriteFlatPlane* plane;
	Image* pImage;
	RECT planeRect;

	Matrix pMatrix_plane; //oPlane Matrix
	Matrix pMatrix_orig;
	Matrix Scale_orig;
	Matrix Trans_orig;
	const Matrix FlipRot = Matrix(ROT_Y, 3.14f); //I need to fix my plane to be flipped, so I wouldn't need this

	// Image width and pos
	float origWidth = 0;
	float origHeight = 0;

	int origPosX = 0;
	int origPosY = 0;

	// Screen Positons for me to offset from
	int ScreenOffsetX;
	int ScreenOffsetY;

};

#endif _GraphicObject_Sprite