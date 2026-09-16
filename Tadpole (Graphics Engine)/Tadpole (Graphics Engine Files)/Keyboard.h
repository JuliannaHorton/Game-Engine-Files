#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "d3dUtil.h" 
#include <d3dUtil.h>


// Wrapper to buffer users from the internal glfw driver
// Converted to enumeration for type safety - yeah!

enum class FROG_KEY
{
	/* Printable keys */
	KEY_SPACE = 32,
	KEY_APOSTROPHE = 39,  /* ' */
	KEY_COMMA = 44,  /* , */
	KEY_MINUS = 45,  /* - */
	KEY_PERIOD = 46,  /* . */
	KEY_SLASH = 47,  /* / */
	KEY_0 = 48,
	KEY_1 = 49,
	KEY_2 = 50,
	KEY_3 = 51,
	KEY_4 = 52,
	KEY_5 = 53,
	KEY_6 = 54,
	KEY_7 = 55,
	KEY_8 = 56,
	KEY_9 = 57,
	KEY_SEMICOLON = 59,  /* ; */
	KEY_EQUAL = 61,  /* = */
	KEY_A = 65,
	KEY_B = 66,
	KEY_C = 67,
	KEY_D = 68,
	KEY_E = 69,
	KEY_F = 70,
	KEY_G = 71,
	KEY_H = 72,
	KEY_I = 73,
	KEY_J = 74,
	KEY_K = 75,
	KEY_L = 76,
	KEY_M = 77,
	KEY_N = 78,
	KEY_O = 79,
	KEY_P = 80,
	KEY_Q = 81,
	KEY_R = 82,
	KEY_S = 83,
	KEY_T = 84,
	KEY_U = 85,
	KEY_V = 86,
	KEY_W = 87,
	KEY_X = 88,
	KEY_Y = 89,
	KEY_Z = 90,
	KEY_LEFT_BRACKET = 91,  /* [ */
	KEY_BACKSLASH = 92,  /* \ */
	KEY_RIGHT_BRACKET = 93,  /* ] */
	KEY_GRAVE_ACCENT = 96,  /* ` */
	KEY_WORLD_1 = 161, /* non-US #1 */
	KEY_WORLD_2 = 162, /* non-US #2 */

	KEY_ARROW_UP = VK_UP,
	KEY_ARROW_DOWN = VK_DOWN,
	KEY_ARROW_LEFT = VK_LEFT,
	KEY_ARROW_RIGHT = VK_RIGHT,

	/* Function keys */
	KEY_ESCAPE = VK_ESCAPE,
	KEY_ENTER = VK_RETURN,
	KEY_TAB = VK_TAB,
	KEY_BACKSPACE = VK_BACK,
	KEY_INSERT = VK_INSERT,
	KEY_DELETE = VK_DELETE,
	KEY_PAGE_UP = VK_PRIOR,
	KEY_PAGE_DOWN = VK_NEXT,
	KEY_HOME = VK_HOME,
	KEY_END = VK_END,
	KEY_CAPS_LOCK = VK_CAPITAL,
	KEY_SCROLL_LOCK = VK_SCROLL,
	KEY_NUM_LOCK = VK_NUMLOCK,
	KEY_PAUSE = VK_PAUSE,

	/* Function keys F1-F12 */
	KEY_F1 = VK_F1,
	KEY_F2 = VK_F2,
	KEY_F3 = VK_F3,
	KEY_F4 = VK_F4,
	KEY_F5 = VK_F5,
	KEY_F6 = VK_F6,
	KEY_F7 = VK_F7,
	KEY_F8 = VK_F8,
	KEY_F9 = VK_F9,
	KEY_F10 = VK_F10,
	KEY_F11 = VK_F11,
	KEY_F12 = VK_F12,

	/* Keypad keys */
	KEY_KP_0 = VK_NUMPAD0,
	KEY_KP_1 = VK_NUMPAD1,
	KEY_KP_2 = VK_NUMPAD2,
	KEY_KP_3 = VK_NUMPAD3,
	KEY_KP_4 = VK_NUMPAD4,
	KEY_KP_5 = VK_NUMPAD5,
	KEY_KP_6 = VK_NUMPAD6,
	KEY_KP_7 = VK_NUMPAD7,
	KEY_KP_8 = VK_NUMPAD8,
	KEY_KP_9 = VK_NUMPAD9,
	KEY_KP_DECIMAL = VK_DECIMAL,
	KEY_KP_DIVIDE = VK_DIVIDE,
	KEY_KP_MULTIPLY = VK_MULTIPLY,
	KEY_KP_SUBTRACT = VK_SUBTRACT,
	KEY_KP_ADD = VK_ADD,
	KEY_KP_ENTER = VK_RETURN, // Generally handled as VK_RETURN
	KEY_KP_EQUAL = VK_OEM_PLUS, // Typically mapped

	/* Modifiers */
	KEY_LEFT_SHIFT = VK_LSHIFT,
	KEY_LEFT_CONTROL = VK_LCONTROL,
	KEY_LEFT_ALT = VK_LMENU,
	KEY_LEFT_SUPER = VK_LWIN,
	KEY_RIGHT_SHIFT = VK_RSHIFT,
	KEY_RIGHT_CONTROL = VK_RCONTROL,
	KEY_RIGHT_ALT = VK_RMENU,
	KEY_RIGHT_SUPER = VK_RWIN,
};


class Keyboard
{
private:
	Keyboard();
	~Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard operator=(const Keyboard&) = delete;

	// Get the global access
	Keyboard* GetInstance();

public:
	// Use this to read keyboard
	static bool GetKeyboardState(FROG_KEY key);
};


#endif