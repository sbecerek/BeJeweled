#pragma once
#include <windows.h>
SIZE MeasureSize(HWND hwnd)
{
    //calculates the size of the rectangle
    SIZE size = SIZE();

    RECT rect;
    if (GetWindowRect(hwnd, &rect))
    {
        size.cx = rect.right - rect.left;
        size.cy = rect.bottom - rect.top;
    }
    return size;
}

SIZE MeasureRect(RECT rect)
{
    SIZE size;
    size.cx = rect.right - rect.left;
    size.cy = rect.bottom - rect.top;
    return size;
}

POINT CalculateCenter(HWND hwnd,RECT rect)
{
    //calculates the center of the screen for given window handle
    POINT center = POINT();
    SIZE windowSize = MeasureRect(rect);
    center.x = (GetSystemMetrics(SM_CXSCREEN) - windowSize.cx) / 2;
    center.y = (GetSystemMetrics(SM_CYSCREEN) - windowSize.cy) / 2;
    return center;
}

POINT GetScreenCenter()
{
    //calculates the center of the screen for given window handle
    POINT center = POINT();
    center.x = (GetSystemMetrics(SM_CXSCREEN)) / 2;
    center.y = (GetSystemMetrics(SM_CYSCREEN)) / 2;
    return center;
}
