#pragma once
#include "BaseWindow.h"

class GemWindow : public BaseWindow<GemWindow>
{
protected:
	SIZE size;
    COLORREF color;
public:
	PCWSTR ClassName() const { return L"Gem"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Render();

    //
    BOOL Create(
        PCWSTR lpWindowName,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = CW_USEDEFAULT,
        int y = CW_USEDEFAULT,
        int nWidth = CW_USEDEFAULT,
        int nHeight = CW_USEDEFAULT,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    )
    {
        size.cx = nWidth;
        size.cy = nHeight;
        color = RGB(125, 125, 125);


        WNDCLASS wc = { 0 };

        wc.lpfnWndProc = GemWindow::WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();
        wc.hbrBackground = CreateSolidBrush(RGB(125, 125, 125));

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(
            dwExStyle, ClassName(), lpWindowName, dwStyle, x, y,
            nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this
        );

        return (m_hwnd ? TRUE : FALSE);
    }


	GemWindow()
	{

	}

	~GemWindow() {};


	//getter and setter
	void SetSize(SIZE s) { size = s; }
	SIZE GetSize() { return size; }

};