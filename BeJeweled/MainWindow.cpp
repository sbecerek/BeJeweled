#include "Arithmetics.h"
#include "MainWindow.h"
#include "resource.h"
#include "Utility.h"

BOOL MainWindow::ClearBoard()
{
    for (unsigned int i = 0; i < MAX_GEM_COUNT; i++)
    {
        for (unsigned int j = 0; j < MAX_GEM_COUNT; j++)
        {
            //SendMessage(Gems[i][j].Window(), WM_CLOSE, NULL, NULL);
            //Handle WM_DESTROY no need to send message
            //below function sends WM_DESTROY
            DestroyWindow(Gems[i][j].Window());
        }
    }
    
    return UpdateWindow(Window());

}


BOOL MainWindow::CreateBoard()
{
    for (unsigned int i = 0; i < GetcGem(); i++)
    {
        for (unsigned int j = 0; j < GetcGem(); j++)
        {
            if (Gems[i][j].Create(L"gem",  WS_CHILDWINDOW | WS_VISIBLE, NULL, 
              5 + i * GetsGem().cx + i * 10, 
              5 + j * GetsGem().cy + j * 10, GetsGem().cx, GetsGem().cy, Window(), NULL))
            {
                //pass from main window to Gem object
                Gems[i][j].SetSize(GetsGem().cx, GetsGem().cy);
                Gems[i][j].SetPosition(5 + i * GetsGem().cx + i * 10, 5 + j * GetsGem().cy + j * 10);

                HBRUSH hbrush = CreateSolidBrush(RGB(55,55,55));
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

BOOL MainWindow::AdjustWindow()
{
    //use required fields to set rectangle of client area
    RECT clientToWindowRect;
    clientToWindowRect.left = GetScreenCenter().x - GetClientSize().cx / 2;
    clientToWindowRect.top = GetScreenCenter().y - GetClientSize().cy / 2;
    clientToWindowRect.right = GetScreenCenter().x + GetClientSize().cx / 2;
    clientToWindowRect.bottom = GetScreenCenter().y + GetClientSize().cy / 2;
    //send it to  AdjustWindowRect()
    if (!AdjustWindowRect(&clientToWindowRect, WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN | WS_VISIBLE, TRUE))
    {
        GetLastError();
        return FALSE;
    }
    //use rectangle in MoveWindow()
    if (!MoveWindow(this->Window(), CalculateCenter(this->Window(), clientToWindowRect).x, CalculateCenter(this->Window(), clientToWindowRect).y, MeasureRect(clientToWindowRect).cx, MeasureRect(clientToWindowRect).cy, TRUE))
    {
        GetLastError();
        return FALSE;
    }
    return TRUE;
}

void MainWindow::OnBoardSizeSmall()
{
    ClearBoard();
    this->cGem = 8;
    this->sGem.cx = 80; this->sGem.cy = 80;
    SIZE s; s.cx = s.cy = cGem * (sGem.cx +  10);
    this->SetClientSize(s);

    

    AdjustWindow();
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

    AdjustWindow();
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

    AdjustWindow();
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
