#pragma once
#include "Window.hpp"
#include "KeyboardClass.hpp"

class EngineContainer
{
public:
	LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
protected:
	Window m_window;
	KeyboardClass m_keyboard;
};

