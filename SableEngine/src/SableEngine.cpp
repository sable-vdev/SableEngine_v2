#include "SableEngine.hpp"

bool SableEngine::Initialize(LPCWSTR title, int width, int height, bool fullscreen)
{
#ifndef NDEBUG
	CreateConsole();
#endif // NDEBUG

	m_window = std::make_unique<Window>();

	if (!m_window->Initialize(title, width, height, fullscreen))
	{
		Logger::Log(ERROR, "Failed to initialize the window class.");
		return false;
	}

	m_keyboard = std::make_unique<KeyboardClass>();

	return true;
}

void SableEngine::Run()
{
	while (m_window->Run())
	{

	}
}

void SableEngine::Shutdown()
{
	if (m_window)
	{
		m_window->Shutdown();
	}
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
