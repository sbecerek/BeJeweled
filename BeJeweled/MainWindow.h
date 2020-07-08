#pragma once
#include "BaseWindow.h"


class MainWindow : public BaseWindow<MainWindow>
{
protected:
	SIZE size;

public:
	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//constructor
	MainWindow()
	{
		size.cx = 720;
		size.cy = 720;
	}

	//getter and setter
	void SetSize(SIZE s) { size = s; }
	SIZE GetSize() { return size ; }



};