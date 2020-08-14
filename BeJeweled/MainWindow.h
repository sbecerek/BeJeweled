#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <windows.h>
#include <string>
#include "BaseWindow.h"
#include "GemWindow.h"





class MainWindow : public BaseWindow<MainWindow>
{
protected:
	//size holds the size of the window
	SIZE clientSize;	//size of the window
	SIZE sGem;	//size of a single Gem. this value to be passed by the main window to created gem
	unsigned int cGem;	//count of the tiles


	//vector holding the gems

public:
	


	static BOOL Initializing;
	


	PCWSTR ClassName() const { return L"Main Window"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnBoardSizeSmall();
	void OnBoardSizeMedium();
	void OnBoardSizeBig();
	void OnNewGame();

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



	DWORD CheckItem(UINT hItem, HMENU hmenu);


};

#endif // !MAINWINDOW_H