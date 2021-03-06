#include <ctime>
#include "MainWindow.h"
#include "Arithmetics.h"
#include "resource.h"
#include "BeJeweled.h"


BOOL MainWindow::Initializing = FALSE;


DWORD MainWindow::CheckItem(UINT hItem, HMENU hmenu)
{
	//First uncheck all
	CheckMenuItem(hmenu, ID_BOARDSIZE_SMALL, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenu, ID_BOARDSIZE_MEDIUM, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenu, ID_BOARDSIZE_BIG, MF_BYCOMMAND | MF_UNCHECKED);
	//then check the hItem
	return CheckMenuItem(hmenu, hItem, MF_BYCOMMAND | MF_CHECKED);
}

void MainWindow::OnNewGame()
{
    Initializing = TRUE;
    std::srand((unsigned int)std::time(nullptr));
    for (int i = 0; i < GetcGem(); i++)
    {
        for (int j = 0; j < GetcGem(); j++)
        {
        	//randomize a color from the colorset
            auto elem = BeJeweled::GetInstance().colorSet.cbegin();
            std::advance(elem, std::rand() % BeJeweled::GetInstance().colorSet.size());

            //SetClassLongPtr(Gems[i][j].Window(), GCLP_HBRBACKGROUND, (LONG_PTR)elem->second);
            BeJeweled::GetInstance().Gems[j][i].SetColor(elem->second);
            InvalidateRect(BeJeweled::GetInstance().Gems[j][i].Window(), NULL, TRUE);
            UpdateWindow(BeJeweled::GetInstance().Gems[j][i].Window());


            if( j - 1 >= 0)
            {
                BeJeweled::GetInstance().Gems[j][i].LEFT = &BeJeweled::GetInstance().Gems[j - 1 ][i];
            }
            else
                BeJeweled::GetInstance().Gems[j][i].LEFT = nullptr;
        	if(i - 1 >= 0 )
        	{
                BeJeweled::GetInstance().Gems[j][i].TOP = &BeJeweled::GetInstance().Gems[j][i - 1];
        	}
            else
                BeJeweled::GetInstance().Gems[j][i].TOP = nullptr;
        	if( i + 1 <= cGem)
        	{
                BeJeweled::GetInstance().Gems[j][i].BOTTOM = &BeJeweled::GetInstance().Gems[j][i + 1];
        	}
            else
                BeJeweled::GetInstance().Gems[j][i].BOTTOM = nullptr;
        	if(j + 1 <= cGem)
        	{
                BeJeweled::GetInstance().Gems[j][i].RIGHT = &BeJeweled::GetInstance().Gems[j + 1][i];
        	}
            else
                BeJeweled::GetInstance().Gems[j][i].RIGHT = nullptr;




            //Instead I think we can use timer to give animation feeling
            //but that seems too much work
            Sleep(50);
        }
    }
    

}

BOOL MainWindow::ClearBoard()
{
    for (unsigned int i = 0; i < MAX_GEM_COUNT; i++)
    {
        for (unsigned int j = 0; j < MAX_GEM_COUNT; j++)
        {
            //SendMessage(Gems[i][j].Window(), WM_CLOSE, NULL, NULL);
            //Handle WM_DESTROY no need to send message
            //below function sends WM_DESTROY
            DestroyWindow(BeJeweled::GetInstance().Gems[i][j].Window());
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
            if (BeJeweled::GetInstance().Gems[i][j].Create(L"gem",  WS_CHILDWINDOW | WS_VISIBLE, NULL,
              5 + i * GetsGem().cx + i * 10, 
              5 + j * GetsGem().cy + j * 10, GetsGem().cx, GetsGem().cy, Window(), NULL))
            {
                //pass from main window to Gem object
                BeJeweled::GetInstance().Gems[i][j].SetSize(GetsGem().cx, GetsGem().cy);
                BeJeweled::GetInstance().Gems[i][j].SetPosition(5 + i * GetsGem().cx + i * 10, 5 + j * GetsGem().cy + j * 10);
                BeJeweled::GetInstance().Gems[i][j].SetColor(RGB(55, 55, 55));

                HBRUSH hbrush = CreateSolidBrush(RGB(55,55,55));
                HBRUSH hOldBrush = (HBRUSH)SetClassLongPtr(BeJeweled::GetInstance().Gems[i][j].Window(), GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
                DeleteObject(hOldBrush);
                InvalidateRect(BeJeweled::GetInstance().Gems[i][j].Window(), NULL, TRUE);


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
    InvalidateRect(Window(), NULL, TRUE);
    CreateBoard();
    

    //this is the last thing to do
    CheckItem(ID_BOARDSIZE_SMALL, GetMenu(this->Window()));


}

void MainWindow::OnBoardSizeMedium()
{
    ClearBoard();
    this->cGem = 10;
    this->sGem.cx = 70; this->sGem.cy = 70;
    SIZE s; s.cx = s.cy = cGem * (sGem.cx + 10);
    this->SetClientSize(s);

    AdjustWindow();
    InvalidateRect(Window(), NULL, TRUE);
    CreateBoard();
    


    CheckItem(ID_BOARDSIZE_MEDIUM, GetMenu(this->Window()));
}

void MainWindow::OnBoardSizeBig()
{
    ClearBoard();
    this->cGem = 12;
    this->sGem.cx = 60; this->sGem.cy = 60;
    SIZE s; s.cx = s.cy = cGem * (sGem.cx + 10);
    this->SetClientSize(s);

    AdjustWindow();
    InvalidateRect(Window(), NULL, TRUE);
    CreateBoard();
    



    CheckItem(ID_BOARDSIZE_BIG, GetMenu(this->Window()));

}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        //identify menu item
        if(!Initializing)
        switch (LOWORD(wParam))
        {

        case ID_BOARDSIZE_SMALL:
        {
            BeJeweled::GetInstance().Initialized = FALSE;
            OnBoardSizeSmall();

        }break;

        case ID_BOARDSIZE_MEDIUM:
        {
            BeJeweled::GetInstance().Initialized = FALSE;
            OnBoardSizeMedium();

        }break;

        case ID_BOARDSIZE_BIG:
        {
            BeJeweled::GetInstance().Initialized = FALSE;
            OnBoardSizeBig();
                
        }break;

        case ID_GAME_NEWGAME:
        {
            //initialize color
            OnNewGame();
            Initializing = FALSE;
            BeJeweled::GetInstance().Initialized = TRUE;
        }break;

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
