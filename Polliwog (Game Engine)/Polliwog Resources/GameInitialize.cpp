
#include "../Finalsprint/Polliwog Engine/Tadpole.h"

void Tadpole::GameInitialize()
{
	name = "Matrices and Movement";
	WindowColor = Colors::DarkBlue;
	this->setWindowName(name);
	this->setWindowColor(WindowColor);

	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	this->setWidthHeight((rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2);  // 1/4 of the screen
}