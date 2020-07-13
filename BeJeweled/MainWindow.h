#pragma once
#include "resource.h"
#include <windows.h>
#include "BaseWindow.h"


class MainWindow : public BaseWindow<MainWindow>
{
protected:
	//size holds the size of the window
	SIZE size;
	int cTile;	//count of the tiles


public:
	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void OnBoardSizeSmall();
	void OnBoardSizeMedium();
	void OnBoardSizeBig();

	//constructor
	MainWindow()
	{
		OnBoardSizeSmall();
	}

	//getter and setter
	void SetSize(SIZE s) { size = s; }
	SIZE GetSize() { return size ; }




};