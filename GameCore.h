#pragma once
#include "Dungeon_map.h"

namespace raylib {
#include "raylib.h"
}
#include "hero.h"
#include "monstre.h"
class GameCore
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------
	static const int SCREENWIDTH = 1280;
	static const int SCREENHEIGHT = 720;
	Dungeon_map TheDungeon;
	Hero hero;
	Monstre troll;
public:
	GameCore();
	void initGameCore();
	void endGameCore();
	void loopGameCore();
	void MortDuHero(int type);

};

