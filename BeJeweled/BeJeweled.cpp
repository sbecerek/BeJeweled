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
            win.Window(),   // handle to receiving window 
            hAccel,         // handle to active accelerator table 
            &msg))          // message data 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //TranslateMessage(&msg);
        //DispatchMessage(&msg);
    }

    return 0;
}