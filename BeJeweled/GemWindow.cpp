#include "GemWindow.h"

void GemWindow::Render()
{
    HBRUSH brush = CreateSolidBrush(color);
    SetClassLongPtr(this->Window(), GCLP_HBRBACKGROUND, (LONG_PTR)brush);

    InvalidateRect(this->Window(), NULL, TRUE);
}


LRESULT GemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);
    }
    return 0;



    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}