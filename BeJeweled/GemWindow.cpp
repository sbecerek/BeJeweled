#include <iostream>
#include "GemWindow.h"



BOOL GemWindow::tracking = false;

LRESULT GemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        DestroyWindow(Window());
        break;

    case WM_MOUSEMOVE:
    {
        if (!tracking) {
            TrackMouse();
            tracking = true;
        }

    }break;

    case WM_MOUSEHOVER:
    {
        MoveWindow(Window(), GetSize().cx + 4, GetSize().cy + 4, GetPosition().x - 2, GetPosition().y - 2, TRUE);
        InvalidateRect(Window(), NULL, TRUE);
        OutputDebugString(L"MOUSE ENTERED\n");
    }break;

    case WM_MOUSELEAVE:
    {
        MoveWindow(Window(), GetSize().cx, GetSize().cy, GetPosition().x, GetPosition().y, TRUE);
        InvalidateRect(Window(), NULL, TRUE);
        OutputDebugString(L"MOUSE LEFT\n");
        tracking = false;
    }break;


    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        //FillRect(hdc, &ps.rcPaint, CreateSolidBrush(color));
        EndPaint(m_hwnd, &ps);
        //OutputDebugString(L"PAINT\n");
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}