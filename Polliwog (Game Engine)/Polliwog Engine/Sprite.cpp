#include "Sprite.h"
#include "../Polliwog Engine/ImageManager.h"
#include "../Polliwog Engine/ShaderManager.h"
#include "../Polliwog Engine/ModelManager.h"
#include "../../src/Camera.h"

Sprite::Sprite(std::string name)
{

	myRectangle.left = 500;
	myRectangle.top = 500;
	myRectangle.right = 100;
	myRectangle.bottom = 100;


	pGOSprite = new GraphicObject_Sprite((SpriteShader*)ShaderManager::Get(ShaderManager::DefaultShaders::PolliwogSpriteRender), ImageManager::Get(name), myRectangle);

	Center.set(TRANS, 0, 0, 0);

	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	Rot.set(ROT_Z, 0.0f);
	Pos.set(TRANS, 500, 500, 0.0f);

	World = Scale * Rot * Pos * Center;
	pGOSprite->SetWorld(World);
}

Sprite::Sprite(std::string name, RECT size)
	: myRectangle(size)
{
	pGOSprite = new GraphicObject_Sprite((SpriteShader*)ShaderManager::Get(ShaderManager::DefaultShaders::PolliwogSpriteRender), ImageManager::Get(name), size);

	Center.set(TRANS, 0, 0, 0);

	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	Rot.set(ROT_Z, 0.0f);
	Pos.set(TRANS, 500, 500, 0.0f);

	World = Scale * Rot * Pos * Center;
	pGOSprite->SetWorld(World);
}

/// <summary>
/// \ingroup SPRITES
/// \brief Returns the width of the Sprite
/// 
/// </summary>
float Sprite::GetWidth()
{
	RECT rect = pGOSprite->GetImageRect();
	float rectW = (float)rect.right;

	return rectW;
}

/// <summary>
/// \ingroup SPRITES
/// \brief Returns the height of the Sprite
/// 
/// </summary>
float Sprite::GetHeight()
{
	RECT rect = pGOSprite->GetImageRect();
	float rectW = (float)rect.bottom;

	return rectW;
}

/// <summary>
/// \ingroup SPRITES
/// \brief Returns the angle of the Sprite
/// 
/// </summary>
float Sprite::GetAngle()
{
	return angle;
}

/// <summary>
/// \ingroup SPRITES
/// \brief Sets the angle of the Sprite
/// 
/// </summary>
void Sprite::SetAngle(float a)
{
	angle = a;
	Rot = Matrix(ROT_Z, angle);

	World = Scale * Rot * Pos * Center;
	pGOSprite->SetWorld(World);
}

/// <summary>
/// \ingroup SPRITES
/// \brief Sets a new Center for the Sprite to be offset from
/// 
/// \note The default is the Center of the Sprites image
/// </summary>
void Sprite::SetCenter(float offSetx, float offSety)
{
	Center = Matrix(TRANS, offSetx, offSety, 0);

	World = Scale * Rot * Pos * Center;
}

/// <summary>
/// \ingroup SPRITES
/// \brief Sets the sprite's image
/// 
/// </summary>
void Sprite::SetPosition(float x, float y)
{
	Scale.set(SCALE, 1.0f, 1.0f, 1.0f);
	Rot.set(ROT_Z, 0.0f);
	Pos.set(TRANS, x, y, 0.0f);

	World = Scale * Rot * Pos * Center;
	pGOSprite->SetWorld(World);
}

/// <summary>
/// \ingroup SPRITES
/// \brief Sets the scale sprite
/// 
/// </summary>
void Sprite::SetScaleFactor(float scalex, float scaley)
{
	Scale = Matrix(SCALE, scalex, scaley, 0);

	World = Pos * Rot * Scale * Center;
	pGOSprite->SetScale(scalex, scaley);
}

/// <summary>
/// \ingroup SPRITES
/// \brief Sets the scale for the pixel in the Sprites image
/// 
/// </summary>
void Sprite::SetScalePixel(float width, float height) //Oh wait this is incorrect!!!! ...I think
{
	pGOSprite->SetImageRectSize(width, height);
}

/// <summary>
/// \ingroup SPRITES
/// \brief Automatically accesses the 2D Camera for the Sprite
/// 
/// \note Must be called in Draw()
/// </summary>
void Sprite::Render(Camera* man)
{
	pGOSprite->Render(man);
}


Sprite::~Sprite()
{
	delete pGOSprite;
}