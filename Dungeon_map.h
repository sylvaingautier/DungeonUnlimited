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

	raylib::Image map[4];
	std::vector <Environnements::s_Collision_Block> CollisionMap;
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
	bool isCollisionMap(raylib::Rectangle hero, Environnements::s_Collision_Block& Collbox);
	void Init();
	void LoadSprites();
	~Dungeon_map();


};
