#pragma once
#include "EngineContainer.hpp"

class SableEngine : EngineContainer
{
public:
	bool Initialize(LPCWSTR title = L"Sable Engine", int width = 1280, int height = 720, bool fullscreen = false);
	bool Run();
private:
	void Render();
	void Update();
	void Shutdown();
	void CreateConsole();
public:
	float deltaTime;
private:
	int m_fps = 0;
	float m_timer = 0.0f;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_frequency;
};

