#pragma once
#include "Window.hpp"
#include "KeyboardClass.hpp"
#include "MouseClass.hpp"
#include "Graphics.hpp"

class EngineContainer
{
public:
	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
protected:
	RAWINPUTDEVICE m_rawInputDevice;
	Window m_window;
	KeyboardClass m_keyboard;
	MouseClass m_mouse;
	Graphics m_graphics;
};

