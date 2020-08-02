#ifndef  UTILITY_H
#define UTILITY_H


#include "resource.h"
#include <windows.h>


DWORD CheckMenuItem(UINT hItem, HMENU hmenu)
{
	//First uncheck all
	CheckMenuItem(hmenu, ID_BOARDSIZE_SMALL, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenu, ID_BOARDSIZE_MEDIUM, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenu, ID_BOARDSIZE_BIG, MF_BYCOMMAND | MF_UNCHECKED);
	//then check the hItem
	return CheckMenuItem(hmenu, hItem, MF_BYCOMMAND | MF_CHECKED);
}



#endif // ! 