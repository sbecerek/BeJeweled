#pragma once
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

	//constructor
	MainWindow()
	{
		cTile = 8;
		size.cx = 720;
		size.cy = 720;
	}

	//getter and setter
	void SetSize(SIZE s) { size = s; }
	SIZE GetSize() { return size ; }




};