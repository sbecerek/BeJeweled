#include <iostream>
#include <math.h>
#include "GemWindow.h"
#include "BeJeweled.h"

BOOL GemWindow::tracking = false;

void GemWindow::OnMouseClick()
{
    //think more about this
    HDC hdc = GetDC(Window());
    RECT rect = { GetPosition().x + 5,GetPosition().y + 5,GetPosition().x + GetSize().cx - 5, GetPosition().y + GetSize().cy -5 };
    DrawEdge(hdc, &rect, BDR_RAISEDINNER, BF_RECT);

    //ReleaseDC(Window(), hdc);

}


LRESULT GemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        DestroyWindow(Window());
        break;

    case WM_LBUTTONDOWN:
    {
        if (BeJeweled::GetInstance().Initialized)
        {
            OutputDebugString(L"LEFT MOUSE CLICK\n");
            OnMouseClick();
        }
    }break;

    case WM_MOUSEMOVE:
    {
        if (!tracking) {
            TrackMouse();
            tracking = true;
        }

    }break;

    case WM_MOUSEHOVER:
    {
        MoveWindow(Window(), GetPosition().x - 4, GetPosition().y - 4, GetSize().cx + 8, GetSize().cy + 8, TRUE);
        OutputDebugString(L"MOUSE ENTERED\n");
    }break;

    case WM_MOUSELEAVE:
    {
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
                    MoveWindow(Window(), GetPosition().x + 1 * TIMER_COUNTER - 4, GetPosition().y + 1* TIMER_COUNTER - 4, GetSize().cx - 2 * TIMER_COUNTER + 8 , GetSize().cy - 2 * TIMER_COUNTER + 8, TRUE);
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
        FillRect(hdc, &ps.rcPaint, CreateSolidBrush(color));
        EndPaint(m_hwnd, &ps);
        OutputDebugString(L"PAINT\n");
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}