#pragma once
namespace raylib {
#include "raylib.h"
}
#include "Block.h"

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
	struct s_Collision_Block
	{
		raylib::Rectangle Box;
		int Type; //0=mur ==> pas de id
		//1=block qui peut disparaitre de la liste ==> id= y*size_x + x
		int Id;   //==> si Type=1 alors id= y*size_x + x

	};

	Block m_Block;
public:
	Environnements();
	void Init();
	~Environnements();
	raylib::Vector2 getTile(int index);
};

