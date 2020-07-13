#pragma once
#include <windows.h>
#include <vector>
#include "resource.h"
#include "BaseWindow.h"
#include "GemWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
protected:
	//size holds the size of the window
	SIZE size;	//size of the window
	SIZE sGem;	//size of a single Gem
	int cGem;	//count of the tiles


	//vector holding the gems
	std::vector<std::vector<GemWindow>> Gems;

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