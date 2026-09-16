#include "GraphicObject_Sprite.h"
#include "Camera.h"
#include "RenderAttorney.h"

GraphicObject_Sprite::GraphicObject_Sprite(SpriteShader* shader, Image* image, RECT rect)
	: pShader(shader), pImage(image), planeRect(rect)
{
	origWidth = image->getRectangle().right - image->getRectangle().left;
	origHeight = image->getRectangle().bottom - image->getRectangle().top;

	origPosX = image->getRectangle().left;
	origPosY = image->getRectangle().top;

	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	ScreenOffsetX = (float)((rc.right - rc.left)*0.5f) * 0.5f;
	ScreenOffsetY = (float)((rc.bottom - rc.top)*0.5f) * 0.5f;

	plane = new SpriteFlatPlane(1, 1, 1);
	Scale_orig = Matrix(SCALE, rect.right, rect.bottom, 1);
	pMatrix_orig = Scale_orig * FlipRot; //This iw

	Matrix Trans = Matrix(TRANS, (float)rect.left, (float)rect.top, 5.0f);

	pMatrix_plane = pMatrix_orig * Trans;

	Trans_orig = Matrix(TRANS, pMatrix_plane.get(ROW_3));

}

GraphicObject_Sprite::~GraphicObject_Sprite()
{
	delete plane;
}


void GraphicObject_Sprite::SetWorld(const Matrix& m)
{
	//translate the received matrix pos to the screen
	float x = m.get(ROW_3).X() - ScreenOffsetX;
	float y = m.get(ROW_3).Y() - ScreenOffsetY;

	Matrix Trans = m;
	Trans.M12() = x;
	Trans.M13() = y;
	Trans.M14() = 5.0f;

	Trans_orig = Matrix(TRANS, Trans.get(ROW_3));

	//Get the scale
	pMatrix_plane = pMatrix_orig * Trans;
}

void GraphicObject_Sprite::SetScale(const int w, const int h)
{
	Scale_orig = Matrix(SCALE, planeRect.right * w, planeRect.bottom * h, 1);
	pMatrix_plane = Scale_orig * FlipRot * Trans_orig;
}

void GraphicObject_Sprite::SetImageRectPos(int x, int y)
{
	origPosX = x;
	origPosY = y;
	
	pImage->setRectangle(origPosX, origPosY, origWidth, origHeight);
}

void GraphicObject_Sprite::SetImageRectSize(int w, int h)
{
	origWidth = w;
	origHeight = h;

	pImage->setRectangle(origPosX, origPosY, origWidth, origHeight);
}


void GraphicObject_Sprite::Render(Camera* mCam)
{
	RenderAttorney::GraphicObjects::BlendOn();

	pImage->Render(pShader, pMatrix_plane);
	pShader->SendCamMatrices(Matrix(IDENTITY), mCam->getOrthoMatrix()); //Perspective just for a quick test
	pShader->SetToContext();
	plane->Render();

	RenderAttorney::GraphicObjects::BlendOff();
}