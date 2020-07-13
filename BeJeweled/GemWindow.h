#pragma once
#include "BaseWindow.h"

class GemWindow : public BaseWindow<GemWindow>
{
protected:

public:
	PCWSTR ClassName() const { return L"Gem"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};