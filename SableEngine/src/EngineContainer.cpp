#include "EngineContainer.hpp"

LRESULT EngineContainer::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        m_input.m_eventType[c] = EventType::KeyDown;
        return 0;
    }
    case WM_KEYUP:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        m_input.m_eventType[c] = EventType::KeyUp;
        return 0;
    }
    case WM_CHAR:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        m_input.PushCharacter(c);
        return 0;
    }
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}
