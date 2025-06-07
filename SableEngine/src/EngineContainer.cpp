#include "EngineContainer.hpp"

LRESULT EngineContainer::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_KEYDOWN:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        m_keyboard.OnKeyDown(c);
        return 0;
    }
    case WM_KEYUP:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        m_keyboard.OnKeyUp(c);
        return 0;
    }
    case WM_CHAR:
    {
        unsigned char c = static_cast<unsigned char>(wparam);
        m_keyboard.OnChar(c);
        return 0;
    }
    case WM_MOUSEMOVE:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnMouseMove(x, y);
        return 0;
    }
    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnLeftPressed(x, y);
        return 0;
    }
    case WM_LBUTTONUP:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnLeftReleased(x, y);
        return 0;
    }
    case WM_RBUTTONDOWN:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnRightPressed(x, y);
        return 0;
    }
    case WM_RBUTTONUP: 
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnRightReleased(x, y);
        return 0;
    }
    case WM_MBUTTONDOWN:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnMiddlePressed(x, y);
        return 0;
    }
    case WM_MBUTTONUP:
    {
        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        m_mouse.OnMiddleReleased(x, y);
        return 0;
    }
    case WM_MOUSEWHEEL:
    {

        int x = LOWORD(lparam);
        int y = HIWORD(lparam);
        auto delta = GET_WHEEL_DELTA_WPARAM(wparam);
        if (delta > 0)
        {
            m_mouse.OnWheelUp(x, y);
        }
        else if (delta < 0)
        {
            m_mouse.OnWheelDown(x, y);
        }
        return 0;
    }
    case RIM_INPUT:
    {
        UINT data;
        GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, nullptr, &data, sizeof(RAWINPUTHEADER));
        if (data > 0)
        {
            std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(data);
            if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lparam), RID_INPUT, rawdata.get(), &data, sizeof(RAWINPUTHEADER)))
            {
                RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
                if (raw->header.dwType == RIM_TYPEMOUSE)
                {
                    m_mouse.OnMouseRawMove(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
                }
            }
        }
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}
