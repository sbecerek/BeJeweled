#pragma once
#include <windows.h>
SIZE MeasureSize(HWND hwnd)
{
    //calculates the center of the screen;
    SIZE size = SIZE();

    RECT rect;
    if (GetWindowRect(hwnd, &rect))
    {
        size.cx = rect.right - rect.left;
        size.cy = rect.bottom - rect.top;
    }
    return size;
}

POINT CalculateCenter(HWND hwnd)
{
    //calculates the center of the screen for given window handle
    POINT center = POINT();
    SIZE windowSize = MeasureSize(hwnd);
    center.x = (GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2;
    center.y = (GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;
    return center;
}

