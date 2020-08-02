#include <windows.h>
#include "MainWindow.h"
#include "resource.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    MainWindow win;
    
    //create main window
    if (!win.Create(L"Suheyb\'s BeJeweled", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN | WS_VISIBLE , NULL , CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL, LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU))))
    {
        return 0;
    }


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