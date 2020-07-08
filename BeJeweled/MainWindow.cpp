#include "Arithmetics.h"
#include "MainWindow.h"
#include "resource.h"


void MainWindow::OnBoardSizeSmall()
{
    //create tile class work on it
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        //identify menu item
        switch (LOWORD(wParam))
        {

        case ID_BOARDSIZE_SMALL:
        {
            SIZE s; s.cx = 720; s.cy = 720;
            this->SetSize(s);
            MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetSize().cx, this->GetSize().cy, FALSE);

            break;
        }

        case ID_BOARDSIZE_MEDIUM:
        {
            SIZE s; s.cx = 765; s.cy = 765;
            this->SetSize(s);
            MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetSize().cx, this->GetSize().cy, FALSE);



            InvalidateRect(this->m_hwnd, NULL, TRUE);
            break;
        }

        case ID_GAME_EXIT:
            PostQuitMessage(0);
            break;


        //help menu
        case ID_HELP_ABOUT:
            MessageBox(this->m_hwnd, L"BeJeweled version 0.1", L"About", MB_OK);
            break;

        }

    }return 0;

    case WM_CREATE:
    {
        MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, MeasureSize(this->Window()).cx, MeasureSize(this->Window()).cy, FALSE);

    }return 0;

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
