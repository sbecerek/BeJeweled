#include "GemWindow.h"



BOOL TheButtonToggle = false;

LRESULT GemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        DestroyWindow(Window());
        break;

    case WM_MOUSEMOVE:
    {
        if (TheButtonToggle == false) {
            tagTRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(TRACKMOUSEEVENT);
            tme.dwFlags = TME_HOVER | TME_LEAVE;
            tme.dwHoverTime = HOVER_DEFAULT;
            tme.hwndTrack = Window();
            TheButtonToggle = true;
            TrackMouseEvent(&tme);

            MoveWindow(Window(), GetSize().cx + 4, GetSize().cy + 4, GetPosition().x + 2, GetPosition().y + 2, TRUE);
        }
        UpdateWindow(Window());
        UpdateWindow((HWND)GetClassLongPtr(Window(), GWLP_HWNDPARENT));

    }break;


    case WM_TIMER:
    {

    }break;

    case WM_MOUSELEAVE:
    {
        TheButtonToggle = false;
        MoveWindow(Window(), GetSize().cx, GetSize().cy, GetPosition().x, GetPosition().y, TRUE);
        UpdateWindow(Window());
        UpdateWindow((HWND)GetClassLongPtr(Window(), GWLP_HWNDPARENT));
    }break;


    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        //FillRect(hdc, &ps.rcPaint, CreateSolidBrush(color));
        EndPaint(m_hwnd, &ps);
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}