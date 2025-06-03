#pragma once
#include <memory>
#include "Window.hpp"
#include "KeyboardClass.hpp"

class SableEngine
{
private:
	std::unique_ptr<Window> m_window;
	std::unique_ptr<KeyboardClass> m_keyboard;
public:
	bool Initialize(LPCWSTR title = L"Sable Engine", int width = 1280, int height = 720, bool fullscreen = false);
	void Run();
	void Shutdown();
private:
	void CreateConsole();
};

