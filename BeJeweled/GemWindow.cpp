#include <iostream>
#include <math.h>
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
        MoveWindow(Window(), GetPosition().x - 2, GetPosition().y - 2, GetSize().cx + 4, GetSize().cy + 4, TRUE);
        OutputDebugString(L"MOUSE ENTERED\n");
    }break;

    case WM_MOUSELEAVE:
    {
        //MoveWindow(Window(), GetPosition().x + 2, GetPosition().y + 2, GetSize().cx - 4, GetSize().cy - 4, TRUE);
        //SetSize(GetSize().cx - 4, GetSize().cy - 4);
        //SetPosition(GetPosition().x + 2, GetPosition().y + 2);
        SetTimer(Window(), this->GEM_TIMER ,50,NULL);
        OutputDebugString(L"MOUSE LEFT\n");
        OutputDebugString(L"PING\n");
        tracking = false;
    }break;

    case WM_TIMER:
    {
        if (wParam == this->GEM_TIMER)
        {
            {
                if (TIMER_COUNTER < 4)
                {
                    TIMER_COUNTER++;
                    MoveWindow(Window(), GetPosition().x + 1 * TIMER_COUNTER/2 - 2, GetPosition().y + 1* TIMER_COUNTER/2 - 2, GetSize().cx - 1 * TIMER_COUNTER + 4, GetSize().cy - 1 * TIMER_COUNTER + 4, TRUE);
                    OutputDebugString(L"PONG\n");
                }
                else
                {
                    KillTimer(Window(), GEM_TIMER);
                    TIMER_COUNTER = 0;
                }
            }
        }
        

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