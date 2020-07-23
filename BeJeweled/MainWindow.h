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
	SIZE sGem;	//size of a single Gem. this value to be passed by the main window to created gem
	unsigned int cGem;	//count of the tiles


	//vector holding the gems

public:
	std::vector<std::vector<GemWindow>> Gems;
	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	BOOL ResizeBoard(unsigned int x);
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

	void SetcGem(int s) { cGem = s; }
	unsigned int GetcGem() { return cGem; }


	//TODO:Write accessors for Gems Container
	//void SetGems(const std::vector<std::vector<GemWindow>>& x) { Gems = x;}
	//const std::vector<std::vector<GemWindow>>& GetGems() const {return Gems;}



};