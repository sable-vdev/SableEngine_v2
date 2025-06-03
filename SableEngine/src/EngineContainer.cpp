#include "EngineContainer.hpp"

LRESULT EngineContainer::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_CHAR:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        if (m_keyboard.autoRepeatChars)
        {
            m_keyboard.OnChar(c);
        }
        else
        {
            const bool wasPressed = lparam & 0x40000000;
            if (!wasPressed)
            {
                m_keyboard.OnChar(c);
            }
        }
    }
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}
