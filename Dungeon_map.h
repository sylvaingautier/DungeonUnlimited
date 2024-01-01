#pragma once
#include "Logger.h"
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include "Environnements.h"


namespace raylib {
#include "raylib.h"
}
using namespace rapidjson;

class Dungeon_map
{

public:
	struct s_Collision_Block
	{
		raylib::BoundingBox Box;
		int Type; //0=mur ==> pas de id
		          //1=block qui peut disparaitre de la liste ==> id= y*size_x + x
		int Id;

	};
	raylib::Image map[4];
	std::vector < struct s_Collision_Block> CollisionMap;
	int sizeMapPixels_x;
	int sizeMapPixels_y;
	Environnements m_Environnement;
	struct s_liste_block
	{
		std::vector<int> Block;

	};
public:
	rapidjson::Document d;
	Dungeon_map();
	void Init();
	void LoadSprites();
	~Dungeon_map();
	bool isCollisionMap(raylib::BoundingBox hero);

};
