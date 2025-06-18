#include "SableEngine.hpp"

bool SableEngine::Initialize(LPCWSTR title, int width, int height, bool fullscreen)
{
#ifndef NDEBUG
	CreateConsole();
#endif // NDEBUG

	QueryPerformanceCounter(&m_lastTime);
	QueryPerformanceFrequency(&m_frequency);

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

	m_graphics = Graphics(m_window.hwnd, width, height, fullscreen, false);

	return true;
}

bool SableEngine::Run()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	deltaTime = static_cast<float>(currentTime.QuadPart - m_lastTime.QuadPart) / m_frequency.QuadPart;

	m_timer += deltaTime;

	if (m_timer >= 1.0f)
	{
		m_timer = 0.0f;

		std::wstring fpsString = m_window.windowTitle;
		fpsString += L" [";
		fpsString += std::to_wstring(m_fps);
		fpsString += L" (";
		fpsString += std::to_wstring(1000.0 / m_fps);
		fpsString += L" ms)]";
		SetWindowText(m_window.hwnd, fpsString.c_str());
		m_fps = 0;
	}
	m_lastTime = currentTime;
	m_fps++;
	if (!m_window.Run()) return false;

	Update();
	Render();

	return true;
}

void SableEngine::Render()
{
	m_graphics.Render();
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
	m_graphics.Shutdown();
#ifndef NDEBUG
	FreeConsole();
	if (m_consoleStderr) fclose(m_consoleStderr);
	if (m_consoleStdout) fclose(m_consoleStdout);
	if (m_consoleStdin) fclose(m_consoleStdin);
#endif
}

void SableEngine::CreateConsole()
{
	AllocConsole();
	freopen_s(&m_consoleStdout, "CONOUT$", "w", stdout);
	freopen_s(&m_consoleStderr, "CONOUT$", "w", stderr);
	freopen_s(&m_consoleStdin, "CONIN$", "r", stdin);

	std::ios::sync_with_stdio();

	Logger::Log(LogLevel::INFO, "Console has been created successfully.");
}
