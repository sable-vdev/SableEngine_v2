#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include "Logger.hpp"

class Window
{
public:
	bool Initialize(LPCWSTR title = L"Sable Engine", int width = 1280, int height = 720, bool fullscreen = false);
	bool Run();
	bool Shutdown();
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
private:
	void CreateWindowClass();
private:
	HWND m_hwnd = nullptr;
	HINSTANCE m_hInstance = nullptr;
	LPCWSTR m_windowTitle = nullptr;
	LPCWSTR m_windowClass = nullptr;
	int m_width = 0;
	int m_height = 0;
	bool m_fullscreen = false;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
};


static Window* WindowHandle = 0;