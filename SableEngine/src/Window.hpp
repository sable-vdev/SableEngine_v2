#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
class Window
{
public:
	Window();
	Window(const Window& other);
	bool Initialize();
	bool Initialize(const char* title = "Sable Engine", int width = 1280, int height = 720, bool fullscreen = false);
	bool Run();
	bool Shutdown();
	~Window();
private:
	void RegisterWindowClass();
private:
	HWND m_handle = nullptr;
	HINSTANCE m_hInstance = nullptr;
	std::string m_windowTitle;
	std::wstring m_windowTitleW;
	std::string m_windowClass;
	std::wstring m_windowClassW;
	int m_width;
	int m_height;
};

