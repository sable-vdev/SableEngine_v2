#include "SableEngine.hpp"

bool SableEngine::Initialize(LPCWSTR title, int width, int height, bool fullscreen)
{
#ifndef NDEBUG
	CreateConsole();
#endif // NDEBUG

	if (!m_window.Initialize(this, title, width, height, fullscreen))
	{
		Logger::Log(ERROR, "Failed to initialize the window class.");
		return false;
	}

	m_rawInputDevice.usUsagePage = 0x01;
	m_rawInputDevice.usUsage = 0x02;

	if (!RegisterRawInputDevices(&m_rawInputDevice, 1, sizeof(m_rawInputDevice)))
	{
		Logger::Log(ERROR, "Failed to initialize the raw input devices.");
		return false;
	}

	m_graphics = Graphics(m_window.hwnd, width, height, fullscreen);

	return true;
}

bool SableEngine::Run()
{
	return m_window.Run();
}

void SableEngine::Update()
{
	if (!m_keyboard.IsCharBufferEmpty())
	{
		Logger::Log(DEBUG, m_keyboard.ReadChar());
	}
}

void SableEngine::Shutdown()
{
	m_window.Shutdown();
}

void SableEngine::CreateConsole()
{
	AllocConsole();

	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);
	freopen_s(&file, "CONIN$", "r", stdin);

	std::ios::sync_with_stdio();

	Logger::Log(LogLevel::INFO, "Console has been created successfully.");
}
