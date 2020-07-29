#pragma once
#include <windows.h>
#include <vector>
#include "resource.h"
#include "BaseWindow.h"
#include "GemWindow.h"

#define MAX_GEM_COUNT 12

class MainWindow : public BaseWindow<MainWindow>
{
protected:
	//size holds the size of the window
	SIZE clientSize;	//size of the window
	SIZE sGem;	//size of a single Gem. this value to be passed by the main window to created gem
	unsigned int cGem;	//count of the tiles


	//vector holding the gems

public:
	GemWindow Gems[MAX_GEM_COUNT][MAX_GEM_COUNT];
	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnBoardSizeSmall();
	void OnBoardSizeMedium();
	void OnBoardSizeBig();

	BOOL CreateBoard();
	BOOL ClearBoard();
	BOOL AdjustWindow();

	//constructor
	MainWindow()
	{
		
	}

	//getter and setter
	void SetClientSize(SIZE s) { clientSize = s; }
	SIZE GetClientSize() { return clientSize ; }

	void SetcGem(int s) { cGem = s; }
	unsigned int GetcGem() { return cGem; }

	void SetsGem(SIZE s) { sGem = s; }
	SIZE GetsGem() { return sGem; }


	//TODO:Write accessors for Gems Container
	//void SetGems(const std::vector<std::vector<GemWindow>>& x) { Gems = x;}
	//const std::vector<std::vector<GemWindow>>& GetGems() const {return Gems;}



};