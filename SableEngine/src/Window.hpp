#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "Logger.hpp"

class EngineContainer;

class Window
{
public:
	bool Initialize(EngineContainer* container, LPCWSTR title = L"Sable Engine", int width = 1280, int height = 720, bool fullscreen = false);
	bool Run();
	bool Shutdown();
private:
	void CreateWindowClass();
public:
	HWND hwnd = nullptr;
private:
	HINSTANCE m_hInstance = nullptr;
	LPCWSTR m_windowTitle = nullptr;
	LPCWSTR m_windowClass = nullptr;
	int m_width = 0;
	int m_height = 0;
	bool m_fullscreen = false;
};


static Window* WindowHandle = 0;