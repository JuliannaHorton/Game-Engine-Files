#include "RenderLog.h"
#include "SpriteString.h"
#include "SpriteFontManager.h"
#include "SceneManager.h"

void RenderLog::Render(const std::vector<std::string>& Messages, int x, int y)
{
	SpriteFont* font = SpriteFontManager::Get(SpriteFontManager::DefaultFonts::PolliwogArialFontBlack);
	for (const std::string& Message : Messages) //Loop through each string
	{
		float pos = (float)x; //Save posx
		for (const char& Character : Message) //loop through each char value
		{
			Sprite* s = font->GetGlyph(Character);

			s->SetPosition(pos, (float)y);
			s->Render(SceneManager::getCurrentScene()->getCamera());
			pos += s->GetWidth();
		}
	}
}