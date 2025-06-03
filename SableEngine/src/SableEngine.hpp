#pragma once
#include "EngineContainer.hpp"

class SableEngine : EngineContainer
{
public:
	bool Initialize(LPCWSTR title = L"Sable Engine", int width = 1280, int height = 720, bool fullscreen = false);
	bool Run();
	void Update();
	void Shutdown();
private:
	void CreateConsole();
};

