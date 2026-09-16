#include "Mouse.h"
#include "Renderer.h"

bool Mouse::GetMouseKeyState(FROG_MOUSE button)
{
	return (GetKeyState((int)button) & 0x08000);
}

// Get cursor
void Mouse::GetCursor(float& xPos, float& yPos)
{
	POINT cursor;
	GetCursorPos(&cursor);

	ScreenToClient(Renderer::GetWindow(), &cursor);

	xPos = cursor.x;
	yPos = cursor.y;
}

// Mouse wheel position
void Mouse::GetWheel(float& pos)
{
	pos;
}

void Mouse::SetWheel(int pos)
{
	pos;
}