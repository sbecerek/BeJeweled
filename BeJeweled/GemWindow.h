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



	GemWindow()
	{

	}

	~GemWindow() {};


	//getter and setter
	void SetSize(SIZE s) { size = s; }
	SIZE GetSize() { return size; }

};