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

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}