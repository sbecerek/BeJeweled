#ifndef BEJEWELED_H
#define BEJEWELED_H
#include <windows.h>

//a singleton static class holds my game objects
class BeJeweled
{
private:
	BeJeweled()
	{
			
	}

	//static BeJeweled* bejeweled_;


public:
	//any game data
	//is stored below
	BOOL Initialized;

	//TODO:refactoring
	//Gems we can store here
	//COlOR map we can store here 

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


};
#endif
