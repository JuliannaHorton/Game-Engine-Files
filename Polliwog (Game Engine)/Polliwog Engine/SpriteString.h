#pragma once

#ifndef _SpriteString
#define _SpriteString

#include <map>
#include <xmllite.h>
#include <list>
#include "../PollywogBog.h"

#include "SpriteFont.h"

class Camera;

class SpriteString
{

public:
	/// <summary>
	/// \ingroup FONT
	///	
	/// The sprite class exists to allows users to add 2D textures to the screen. 
	/// This might include a HUD, Gun Site, icons, ect.
	/// <br>
	/// <br>
	/// To use them your first going to want to load the Font into the game with the SpriteFontManager
	/// \code
	/// LoadResources()
	/// {
	/// ...
	///		SpriteFontManager::LoadDefaultResources();
	///		SpriteFontManager::Load("myFont", "SuperCoolFont"); 
	/// ...
	/// }
	/// \endcode
	/// Now you can use that image as a Sprite in the game!
	/// \code
	/// HUD::HUD()
	/// {
	///		SpriteFont* Font = SpriteFontManager::Get("myFont");
	///		Score = new SpriteString(Font, "Score: ", 30, 500);
	/// }
	/// \endcode
	/// Now the Sprite will appear!
	/// <br>
	/// </summary>
	SpriteString() = default;
	SpriteString(const SpriteString&) = delete;
	SpriteString& operator=(const SpriteString&) = delete;
	~SpriteString() = default;

	SpriteString(SpriteFont* sf, std::string s, int x, int y);

	void Render(Camera* cam);

	float GetHeight();
	float GetWidth();
	void SetPos(int x, int y);
	void SetFont(SpriteFont* sf, std::string s, int x, int y);
	void SetSize(float x, float y);

	void SetNewText(std::string s);
	void AddText(std::string s);


private:
	SpriteFont* myFont;
	std::list<SpriteFont::Glyph*> mySymbols;

	float height = 0;
	float width = 0;
	int posx = 0;
	int posy = 0;
};


#endif _SpriteString