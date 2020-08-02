#pragma once
#include "BaseWindow.h"

class GemWindow : public BaseWindow<GemWindow>
{
protected:
	POINT position;
	SIZE size;
	COLORREF color;
public:
	
	PCWSTR ClassName() const { return L"Gem"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);



	GemWindow()
	{
		color = RGB(125, 125, 125);
	}

	~GemWindow() {};

	//getter and setter
	void SetSize(int x, int y) { size.cx = x; size.cy = y; }
	SIZE GetSize() { return size; }

	void SetPosition(int x, int y) { position.x = x; position.y = y; }
	POINT GetPosition() { return position; }


};