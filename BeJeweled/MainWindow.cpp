#include "Arithmetics.h"
#include "Utility.h"
#include "MainWindow.h"
#include "resource.h"


BOOL MainWindow::CreateBoard()
{
    //create gems
    for (unsigned int i = 0; i < GetcGem(); i++)
    {
        for (unsigned int j = 0; j < GetcGem(); j++)
        {
            if (!Gems[i][j].Create(L"gem", WS_CHILD | WS_VISIBLE, NULL, 5 + i * 80 + i * 5, 5 + j * 80 + j * 5, GetsGem().cx, GetsGem().cy, Window(), NULL))
                return FALSE;
        }
    }
    return TRUE;
}


BOOL MainWindow::ResizeBoard(unsigned int x)
{
    Gems.clear();
    Gems.resize(x);
    for (unsigned int i = 0; i < x; i++)
        Gems[i].resize(x);

    return TRUE;
}

void MainWindow::OnBoardSizeSmall()
{
    this->cGem = 8;
    SIZE s; s.cx = 720; s.cy = 720;
    this->SetSize(s);
    this->sGem.cx = 80; this->sGem.cy = 80;
    MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetSize().cx, this->GetSize().cy, TRUE);


    ResizeBoard(cGem);
    CreateBoard();

    //this is the last thing to do
    CheckMenuItem(ID_BOARDSIZE_SMALL, GetMenu(this->Window()));


}

void MainWindow::OnBoardSizeMedium()
{
    this->cGem = 10;
    SIZE s; s.cx = 800; s.cy = 800;
    this->SetSize(s);
    this->sGem.cx = 70; this->sGem.cy = 70;
    MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetSize().cx, this->GetSize().cy, TRUE);


    ResizeBoard(cGem);
    CreateBoard();

    CheckMenuItem(ID_BOARDSIZE_MEDIUM, GetMenu(this->Window()));

}

void MainWindow::OnBoardSizeBig()
{
    this->cGem = 12;
    SIZE s; s.cx = 840; s.cy = 840;
    this->SetSize(s);
    this->sGem.cx = 60; this->sGem.cy = 60;
    MoveWindow(this->Window(), CalculateCenter(this->Window()).x, CalculateCenter(this->Window()).y, this->GetSize().cx, this->GetSize().cy, TRUE);

    ResizeBoard(cGem);
    CreateBoard();





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
