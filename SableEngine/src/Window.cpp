#include "EngineContainer.hpp"

bool Window::Initialize(EngineContainer* container, LPCWSTR title, int width, int height, bool fullscreen)
{
    m_width = width;
    m_height = height;
    m_fullscreen = fullscreen;
    windowTitle = title;
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
	hwnd = CreateWindowEx(0, m_windowClass, windowTitle, WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SIZEBOX | WS_OVERLAPPEDWINDOW,
		posX, posY, m_width, m_height, nullptr, nullptr, m_hInstance, container);

	if (!hwnd)
	{
		Logger::Log(LogLevel::ERROR, "Failed to create the window.");
		return false;
	}

	//Bring up the window on the screen and set it to focus
	SetWindowText(hwnd, windowTitle);
	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

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
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
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
	if(hwnd)
		DestroyWindow(hwnd);
	hwnd = nullptr;

	//remove application class
	UnregisterClass(m_windowClass, m_hInstance);
	m_hInstance = nullptr;

	return true;
}

LRESULT CALLBACK MessageHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		EngineContainer* const container = reinterpret_cast<EngineContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return container->WindowProc(hwnd, msg, wparam, lparam);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_NCCREATE)
	{
		CREATESTRUCT* create = reinterpret_cast<CREATESTRUCT*>(lparam);
		EngineContainer* window = reinterpret_cast<EngineContainer*> (create->lpCreateParams);
		if (!window)
		{
			Logger::Log(ERROR, "Pointer to EngineContainer is null");
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MessageHandler));
		Logger::Log(INFO, "The window was created successfully.");

		return window->WindowProc(hwnd, msg, wparam, lparam);
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
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