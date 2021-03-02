#ifndef BEJEWELED_H
#define BEJEWELED_H
#include <windows.h>
#include <string>
#include <map>

#define MAX_GEM_COUNT 12

//a singleton static class holds my game objects
class BeJeweled
{
private:
	BeJeweled()
	{
			
	}

	//static BeJeweled* bejeweled_;
	HWND SelectedGem;


public:
	//any game data
	//is stored below
	BOOL Initialized;


	GemWindow Gems[MAX_GEM_COUNT][MAX_GEM_COUNT];
	const std::map<std::string, COLORREF> colorSet{ {"NAVY",RGB(0,0,128)},{"PINK",RGB(255, 105, 180)},{"TURQUISE",RGB(64, 224, 208)},{"RED",RGB(255, 0, 0)},{"YELLOW", RGB(255, 255, 0)},{"GREEN",RGB(0, 255, 0)} };


	/**
	 * Singletons should not be clone able.
	 */
	BeJeweled(BeJeweled& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const BeJeweled&) = delete;

	static BeJeweled& GetInstance()
	{
		static BeJeweled bejeweled_;

		return bejeweled_;
	}

	

	void OnIdle()
	{
		//check for game winning state
		for(auto Gem : Gems)
		{
			//add method to each gem which will return neighbors
		}

	}

	void OnError(const std::string s)
	{

		//this method might not work
		//testing left for later
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;

		std::wstring stemp = r;
		LPCWSTR result = stemp.c_str();

		OutputDebugString(result);
	}

	void SetSelectedGem(HWND g)
	{
		HWND oldGem = SelectedGem;

		if(oldGem != NULL && g != NULL)
		{
		InvalidateRect(oldGem, NULL, TRUE);
		InvalidateRect(g, NULL, TRUE);
			
		}
		else if(oldGem != NULL)
		{
			InvalidateRect(oldGem, NULL, TRUE);

		}
		else
		{
			InvalidateRect(g, NULL, TRUE);

		}
		SelectedGem = g;


	}

	
	HWND GetSelectedGem()
	{
		return SelectedGem;
	}

};
#endif
