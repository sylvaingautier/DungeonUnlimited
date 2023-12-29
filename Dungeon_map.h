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
	Environnements m_Environnement;

public:
	rapidjson::Document d;
	Dungeon_map();
	void Init();
	void LoadSprites();
	~Dungeon_map();

};
