#pragma once
#include "Dungeon_map.h"
namespace raylib {
#include "raylib.h"
}


class GameCore
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------
	static const int SCREENWIDTH = 1280;
	static const int SCREENHEIGHT = 720;
	Dungeon_map test;

public:
	GameCore();
	void initGameCore();
	void endGameCore();
	void loopGameCore();
	
};

