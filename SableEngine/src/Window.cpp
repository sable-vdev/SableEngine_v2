#include "Window.hpp"

bool Window::Initialize(LPCWSTR title, int width, int height, bool fullscreen)
{
    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;
    m_windowTitle = title;
	m_windowClass = L"windowClass";

	WindowHandle = this;

    CreateWindowClass();


	DEVMODE dmScreenSettings;
	int posX, posY;

	//setup the screen settings depending on whether its running in full screen or windowed mode
	if (m_fullscreen)
	{
		//Determine the resolution of the clients desktop scren
		m_width = GetSystemMetrics(SM_CXSCREEN);
		m_height = GetSystemMetrics(SM_CYSCREEN);
		// If full screen set the screen to maxiumum size of the users desktop and 32bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_width;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//Change the display settings to fullscreen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//set the position of the window to the top left corner
		posX = posY = 0;
	}
	else
	{
		//if windowed then set to resolution
		posX = (GetSystemMetrics(SM_CXSCREEN) - m_width) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - m_height) / 2;
	}

	//create the window with the screen settings and set handle to it
	m_hwnd = CreateWindowEx(0, m_windowClass, m_windowTitle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX | WS_OVERLAPPEDWINDOW,
		posX, posY, m_width, m_height, nullptr, nullptr, m_hInstance, this);

	if (!m_hwnd)
	{
		Logger::Log(LogLevel::ERROR, "Failed to create the window.");
		return false;
	}

	//Bring up the window on the screen and set it to focus
	SetWindowText(m_hwnd, m_windowTitle);
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//Hide the mouse cursor
	//ShowCursor(false);

    return true;
}

bool Window::Run()
{
	MSG message;

	//Init the message struct
	ZeroMemory(&message, sizeof(MSG));
	//Handle window messages
	if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//If window signals to end the application then exit
	if (message.message == WM_QUIT)
	{
			return false;
	}

	return true;
}

bool Window::Shutdown()
{
	//show the mouse cursor
	//ShowCursor(true);

	//Fix the display settings if leaving full screen mode
	if (m_fullscreen)
	{
		ChangeDisplaySettings(nullptr, 0);
	}

	//remove the window
	if(m_hwnd)
		DestroyWindow(m_hwnd);
	m_hwnd = nullptr;

	//remove application class
	UnregisterClass(m_windowClass, m_hInstance);
	m_hInstance = nullptr;

	return true;
}

void Window::CreateWindowClass()
{
	WNDCLASSEX wc;

	//get instance of this application
	m_hInstance = GetModuleHandle(nullptr);

	//Setup windows class with default settings
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_windowClass;
	wc.cbSize = sizeof(WNDCLASSEX);

	//Register the window class
	RegisterClassEx(&wc);
}

LRESULT Window::MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	unsigned char c;

	switch (msg)
	{
	case WM_NCCREATE:
		Logger::Log(INFO, "The window was created successfully.");
		return 0;
	case WM_CHAR:
		c = static_cast<unsigned char>(wparam);
		return 0;
	case WM_KEYDOWN:
		c = static_cast<unsigned char>(wparam);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
}

LRESULT Window::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	Window* window = nullptr;

	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lparam);
		window = reinterpret_cast<Window*> (create->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->m_hwnd = hwnd;
	}
	else
	{
		window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (window)
	{
		return window->MessageHandler(hwnd, msg, wparam, lparam);
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}
