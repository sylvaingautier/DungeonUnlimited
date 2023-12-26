#pragma once
namespace raylib {
#include "raylib.h"
}
#include "Environnements.h"
class GameCore
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------
	static const int SCREENWIDTH = 1280;
	static const int SCREENHEIGHT = 720;
	Environnements m_Environnement;

public:
	GameCore();
	void initGameCore();
	void endGameCore();
	void loopGameCore();
	
};

