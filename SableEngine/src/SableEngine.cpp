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
		unsigned char c = m_keyboard.ReadChar();
		if (c == 'a')
		{
			Logger::Log(DEBUG, c);
		}
		
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
