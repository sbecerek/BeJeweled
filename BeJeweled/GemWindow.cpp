#include <iostream>
#include <math.h>
#include "GemWindow.h"
#include "BeJeweled.h"

BOOL GemWindow::tracking = false;

void DrawGemBorder(HWND gemHandle)
{
    //paint rectangle
    RECT rcWind;
    HDC dc = GetDC(gemHandle);
    GetWindowRect(gemHandle, &rcWind);
    RECT rcClient;
    //MoveWindow(hWnd, rcWind.left - 4, rcWind.top - 4, 8 + rcWind.right - rcWind.left, 8 + rcWind.bottom - rcWind.top, TRUE);
    GetClientRect(gemHandle, &rcClient);
    HPEN hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HGDIOBJ hOldPen = SelectObject(dc, hPen);
    SelectObject(dc, GetStockObject(NULL_BRUSH));
    Rectangle(dc, rcClient.left, rcClient.top, rcClient.right, rcClient.bottom);
    DeleteObject(hPen);
}


LRESULT GemWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int num = 0;
    switch (uMsg)
    {
    case WM_DESTROY:
        DestroyWindow(Window());
        break;

    
    case WM_LBUTTONDOWN:
    {

        if(BeJeweled::GetInstance().GetSelectedGem() == Window())
        {
	        //deselect window
            BeJeweled::GetInstance().SetSelectedGem(static_cast<HWND>(nullptr));
        	//paint the color
            //InvalidateRect(Window(),NULL,TRUE );
            
        }
        else if(BeJeweled::GetInstance().Initialized && BeJeweled::GetInstance().GetSelectedGem() != Window())
        {
            //InvalidateRect(GetParent(Window()), NULL, TRUE);
	        //selectwindow
            BeJeweled::GetInstance().SetSelectedGem(Window());
            //InvalidateRect(Window(), NULL, TRUE);
        }
    }
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
        MoveWindow(Window(), GetPosition().x - 4, GetPosition().y - 4, GetSize().cx + 8, GetSize().cy + 8, TRUE);
        InvalidateRect(Window(), NULL, TRUE);
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
                    InvalidateRect(Window(), NULL, TRUE);
                	
                }
                else
                {
                    KillTimer(Window(), GEM_TIMER);
                    TIMER_COUNTER = 0;
                    InvalidateRect(Window(), NULL, TRUE);

                }
            }
        }
        

    }break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, CreateSolidBrush(color));

        if (BeJeweled::GetInstance().GetSelectedGem() == Window())
        {
            DrawGemBorder(Window());
        }
        EndPaint(m_hwnd, &ps);
        OutputDebugString(L"PAINT\n");
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}