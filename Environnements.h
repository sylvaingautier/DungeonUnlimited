#pragma once
namespace raylib {
#include "raylib.h"
}
#include "Block.h"
#include "Block_Interact.h"

class Environnements
{
public:
	//----------------------------------------------------------------------------------
	// Local Variables Definition (local to this module)
	//----------------------------------------------------------------------------------
	raylib::Image m_Tileset;
	int m_TileSize;
	int m_sizeTileSet_x;
	int m_sizeTileSet_y;


	Block m_Block;
public:
	Environnements();
	void Init();
	~Environnements();
	raylib::Vector2 getTile(int index);
};

