#include "SpriteString.h"
#include "SceneManager.h"

SpriteString::SpriteString(SpriteFont* sf, std::string s, int x, int y)
	: myFont(sf), posx(x), posy(y)
{
	//Each character in the string gets converted and pushed into the glyph list


	for (size_t i = 0; i < s.length(); i++)
	{
		mySymbols.push_back(myFont->GetGlyph(s.at(i)));
	}
}

void SpriteString::Render(Camera* cam)
{
	float pos = (float)posx; //Save posx
	for (auto& Character : mySymbols)
	{
		Character->SetPosition(pos, (float)posy); //I feel like I could take out (Character->GetWidth() * 0.5f) somehow
		Character->Render(cam);
		pos += Character->GetWidth(); //Add the current width 
	}
}


//
// Setters and Getters
//

/// <summary>
/// \ingroup FONT
/// \brief SGets the height of the sprite string
/// 
/// </summary>
float SpriteString::GetHeight()
{
	return height;
}

/// <summary>
/// \ingroup FONT
/// \brief Gets the width of the sprite string
/// 
/// </summary>
float SpriteString::GetWidth()
{
	return width;
}

/// <summary>
/// \ingroup FONT
/// \brief Sets the Position of the Sprite string
/// 
/// </summary>
void SpriteString::SetPos(int x, int y)
{
	posx = x;
	posy = y;
}

/// <summary>
/// \ingroup FONT
/// \brief Sets the Position of the Sprite string
/// 
/// </summary>
void SpriteString::SetFont(SpriteFont* sf, std::string s, int x, int y)
{
	myFont = sf;
	posx = x;
	posy = y;

	//Each character in the string gets converted and pushed into the glyph list
	for (size_t i = 0; i < s.length(); i++)
	{
		mySymbols.push_back(myFont->GetGlyph(s.at(i)));
	}
}

/// <summary>
/// \ingroup FONT
/// \brief Sets the Position of the Sprite string
/// 
/// </summary>
void SpriteString::SetSize(float x, float y)
{
	width = x;
	height = y;

	std::list<SpriteFont::Glyph*>::iterator Character;
	for (Character = mySymbols.begin(); Character != mySymbols.end(); Character++)
	{
		(*Character)->SetScaleFactor(x, y);
	}
}

/// <summary>
/// \ingroup FONT
/// \brief Sets the Position of the Sprite string
/// 
/// </summary>
void SpriteString::SetNewText(std::string s)
{
	mySymbols.clear();
	for (size_t i = 0; i < s.length(); i++)
	{
		mySymbols.push_back(myFont->GetGlyph(s.at(i)));
	}
}

/// <summary>
/// \ingroup FONT
/// \brief Sets the Position of the Sprite string
/// 
/// </summary>
void SpriteString::AddText(std::string s)
{
	for (size_t i = 0; i < s.length(); i++)
	{
		mySymbols.push_back(myFont->GetGlyph(s.at(i)));
	}
}
