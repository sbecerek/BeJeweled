#include <windows.h>
#include "MainWindow.h"
#include "resource.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;
    
    if (!win.Create(L"Suheyb\'s BeJeweled", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,NULL ,CW_USEDEFAULT,CW_USEDEFAULT,win.GetSize().cx,win.GetSize().cy,NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU))))
    {
        return 0;
    }

    //maybe here I can call OnBoardSizeSmall
    //when we do OnBoardSizeSmall() in constructor it doesn't init with small size
    //small size is not checked in the menu since menu is not initialized yet
    CheckMenuRadioItem(GetMenu(win.Window()), ID_BOARDSIZE_SMALL, ID_BOARDSIZE_BIG, ID_BOARDSIZE_SMALL, MF_BYCOMMAND);
    ShowWindow(win.Window(), nCmdShow);


    //load the accelerator - shortcuts
    HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR));
    MSG msg = { };

    // Run the message loop.
    while (GetMessage(&msg, NULL, 0, 0))
    {
        //checks for accelerator translation
        //if there is nothing to do from accelerator
        //goes for the normal message loop
        if (!TranslateAccelerator(
            win.Window(),  // handle to receiving window 
            hAccel,         // handle to active accelerator table 
            &msg))         // message data 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //TranslateMessage(&msg);
        //DispatchMessage(&msg);
    }

    return 0;
}