#pragma once

#ifndef _Sprite
#define _Sprite

#include <map>
#include "../Image.h"
#include "../GraphicObject_Sprite.h"

class Camera;

class Sprite
{

public:
	/// <summary>
	/// \ingroup SPRITES
	///	
	/// The sprite class exists to allows users to add 2D textures to the screen. 
	/// This might include a HUD, Gun Site, icons, ect.
	/// <br>
	/// <br>
	/// To use them your first going to want to load the image into the game with the Image Manager
	/// \code
	/// LoadResources()
	/// {
	/// ...
	///		ImageManager::Load("Site", TextureManager::Get("Site"));
	/// ...
	/// }
	/// \endcode
	/// Now you can use that image as a Sprite in the game!
	/// \code
	/// Tank::Tank()
	/// {
	///	 ...
	///		GunSite = new Sprite("Site");
	/// 
	/// 	GunSite->SetCenter(0, 0);
	///		GunSite->SetAngle(0);
	///		GunSite->SetScaleFactor(3, 3);
	///		GunSite->SetScalePixel(1, 1);
	///		GunSite->SetPosition(100, 100);
	///  ...
	/// }
	/// \endcode
	/// Now the Sprite will appear!
	/// <br>
	/// </summary>
	Sprite() = default;
	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;
	~Sprite();

	Sprite(std::string imgKey);
	Sprite(std::string name, RECT size);

	void Render(Camera* man);

	//
	// Sets up the sprite based on user specification
	//
	float GetAngle();
	void SetAngle(float a);
	void SetCenter(float offSetx, float offSety);
	void SetPosition(float x, float y);
	void SetScaleFactor(float scalex, float scaley);
	void SetScalePixel(float width, float height);

	float GetWidth();
	float GetHeight();


private:
	float angle = 0;
	float centerX = 0;
	float centerY = 0;

	float scaleX = 0;
	float scaleY = 0;
	GraphicObject_Sprite* pGOSprite = nullptr;

	Matrix Pos;
	Matrix Scale;
	Matrix Rot;
	Matrix World;
	Matrix Center;

	Vect Centerpoint;
	RECT myRectangle;

};


#endif _Sprite