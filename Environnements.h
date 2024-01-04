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
				  //1=porte // grille sans clé
		          //2=porte à verou 
		int x;
		int y;   

	};

	Block m_Block;
public:
	Environnements();
	void Init();
	~Environnements();
	raylib::Vector2 getTile(int index);
};

