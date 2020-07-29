#include "Arithmetics.h"
#include "Utility.h"
#include "MainWindow.h"
#include "resource.h"

BOOL MainWindow::ClearBoard()
{
    for (unsigned int i = 0; i < 12; i++)
    {
        for (unsigned int j = 0; j < 12; j++)
        {
            //DestroyWindow() closes all associated windows
            SendMessage(Gems[i][j].Window(), WM_CLOSE, NULL, NULL);
        }
    }

    UpdateWindow(Window());
    return TRUE;
}


BOOL MainWindow::CreateBoard()
{
    for (unsigned int i = 0; i < GetcGem(); i++)
    {
        for (unsigned int j = 0; j < GetcGem(); j++)
        {
            if (Gems[i][j].Create(L"gem", WS_CHILD | WS_VISIBLE, NULL, 5 + i * GetsGem().cx + i * 5, 5 + j * GetsGem().cy + j * 5, GetsGem().cx, GetsGem().cy, Window(), NULL))
            {
                
                HBRUSH hbrush = CreateSolidBrush(RGB(125,125,125));//rgb hexadecimal
                HBRUSH hOldBrush = (HBRUSH)SetClassLongPtr(Gems[i][j].Window(), GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
                DeleteObject(hOldBrush);
                InvalidateRect(Gems[i][j].Window(), NULL, TRUE);

            }
            else
            {
                return FALSE;
            }
        }

    }
    return TRUE;
}


void MainWindow::OnBoardSizeSmall()
{
    ClearBoard();
    this->cGem = 8;
    this->sGem.cx = 80; this->sGem.cy = 80;
    SIZE s; s.cx = s.cy = cGem * (sGem.cx + 10) ;
    this->SetClientSize(s);

    //can't do shit if the window is not displaying yet

    
    MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetClientSize().cx, this->GetClientSize().cy, TRUE);


    CreateBoard();
    InvalidateRect(Window(), NULL, TRUE);

    //this is the last thing to do
    CheckMenuItem(ID_BOARDSIZE_SMALL, GetMenu(this->Window()));


}

void MainWindow::OnBoardSizeMedium()
{
    ClearBoard();
    this->cGem = 10;
    this->sGem.cx = 70; this->sGem.cy = 70;
    SIZE s; s.cx = s.cy = cGem * (sGem.cx + 10);
    this->SetClientSize(s);
    MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetClientSize().cx, this->GetClientSize().cy, TRUE);

    CreateBoard();
    InvalidateRect(Window(), NULL, TRUE);


    CheckMenuItem(ID_BOARDSIZE_MEDIUM, GetMenu(this->Window()));
}

void MainWindow::OnBoardSizeBig()
{
    ClearBoard();
    this->cGem = 12;
    this->sGem.cx = 60; this->sGem.cy = 60;
    SIZE s; s.cx = s.cy = cGem * (sGem.cx + 10);
    this->SetClientSize(s);
    MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetClientSize().cx, this->GetClientSize().cy, TRUE);

    CreateBoard();
    InvalidateRect(Window(), NULL, TRUE);




    CheckMenuItem(ID_BOARDSIZE_BIG, GetMenu(this->Window()));

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
            OnBoardSizeSmall();

            break;
        }

        case ID_BOARDSIZE_MEDIUM:
        {
            OnBoardSizeMedium();

            break;
        }

        case ID_BOARDSIZE_BIG:
        {
            OnBoardSizeBig();
                
            break;
        }

        case ID_GAME_NEWGAME:
        {
            //initialize color
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
       //MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, MeasureSize(this->Window()).cx, MeasureSize(this->Window()).cy, FALSE);
       //CreateBoard();
        OnBoardSizeSmall();

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
