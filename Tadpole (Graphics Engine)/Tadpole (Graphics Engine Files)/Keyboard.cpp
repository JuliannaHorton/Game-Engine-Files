#include "Keyboard.h"

bool Keyboard::GetKeyboardState(FROG_KEY key)
{
	return (GetKeyState((int)key) & 0x08000);
}