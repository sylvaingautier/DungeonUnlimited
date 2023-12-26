#pragma once
namespace raylib {
#include "raylib.h"
}

class Environnements
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------
	raylib::Image m_Tileset;
	raylib::Texture2D texture;

public:
	Environnements();
	void initEnvironnements();
	~Environnements();
};

